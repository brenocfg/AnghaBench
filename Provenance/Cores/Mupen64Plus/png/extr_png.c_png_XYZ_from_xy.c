#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ redx; scalar_t__ redy; scalar_t__ greenx; scalar_t__ greeny; scalar_t__ bluex; scalar_t__ bluey; scalar_t__ whitex; int whitey; } ;
typedef  TYPE_1__ png_xy ;
typedef  scalar_t__ png_fixed_point ;
struct TYPE_6__ {scalar_t__ red_X; scalar_t__ red_Y; scalar_t__ red_Z; scalar_t__ green_X; scalar_t__ green_Y; scalar_t__ green_Z; scalar_t__ blue_X; scalar_t__ blue_Y; scalar_t__ blue_Z; } ;
typedef  TYPE_2__ png_XYZ ;

/* Variables and functions */
 scalar_t__ PNG_FP_1 ; 
 scalar_t__ png_muldiv (scalar_t__*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ png_reciprocal (scalar_t__) ; 

__attribute__((used)) static int
png_XYZ_from_xy(png_XYZ *XYZ, const png_xy *xy)
{
   png_fixed_point red_inverse, green_inverse, blue_scale;
   png_fixed_point left, right, denominator;

   /* Check xy and, implicitly, z.  Note that wide gamut color spaces typically
    * have end points with 0 tristimulus values (these are impossible end
    * points, but they are used to cover the possible colors).  We check
    * xy->whitey against 5, not 0, to avoid a possible integer overflow.
    */
   if (xy->redx   < 0 || xy->redx > PNG_FP_1) return 1;
   if (xy->redy   < 0 || xy->redy > PNG_FP_1-xy->redx) return 1;
   if (xy->greenx < 0 || xy->greenx > PNG_FP_1) return 1;
   if (xy->greeny < 0 || xy->greeny > PNG_FP_1-xy->greenx) return 1;
   if (xy->bluex  < 0 || xy->bluex > PNG_FP_1) return 1;
   if (xy->bluey  < 0 || xy->bluey > PNG_FP_1-xy->bluex) return 1;
   if (xy->whitex < 0 || xy->whitex > PNG_FP_1) return 1;
   if (xy->whitey < 5 || xy->whitey > PNG_FP_1-xy->whitex) return 1;

   /* The reverse calculation is more difficult because the original tristimulus
    * value had 9 independent values (red,green,blue)x(X,Y,Z) however only 8
    * derived values were recorded in the cHRM chunk;
    * (red,green,blue,white)x(x,y).  This loses one degree of freedom and
    * therefore an arbitrary ninth value has to be introduced to undo the
    * original transformations.
    *
    * Think of the original end-points as points in (X,Y,Z) space.  The
    * chromaticity values (c) have the property:
    *
    *           C
    *   c = ---------
    *       X + Y + Z
    *
    * For each c (x,y,z) from the corresponding original C (X,Y,Z).  Thus the
    * three chromaticity values (x,y,z) for each end-point obey the
    * relationship:
    *
    *   x + y + z = 1
    *
    * This describes the plane in (X,Y,Z) space that intersects each axis at the
    * value 1.0; call this the chromaticity plane.  Thus the chromaticity
    * calculation has scaled each end-point so that it is on the x+y+z=1 plane
    * and chromaticity is the intersection of the vector from the origin to the
    * (X,Y,Z) value with the chromaticity plane.
    *
    * To fully invert the chromaticity calculation we would need the three
    * end-point scale factors, (red-scale, green-scale, blue-scale), but these
    * were not recorded.  Instead we calculated the reference white (X,Y,Z) and
    * recorded the chromaticity of this.  The reference white (X,Y,Z) would have
    * given all three of the scale factors since:
    *
    *    color-C = color-c * color-scale
    *    white-C = red-C + green-C + blue-C
    *            = red-c*red-scale + green-c*green-scale + blue-c*blue-scale
    *
    * But cHRM records only white-x and white-y, so we have lost the white scale
    * factor:
    *
    *    white-C = white-c*white-scale
    *
    * To handle this the inverse transformation makes an arbitrary assumption
    * about white-scale:
    *
    *    Assume: white-Y = 1.0
    *    Hence:  white-scale = 1/white-y
    *    Or:     red-Y + green-Y + blue-Y = 1.0
    *
    * Notice the last statement of the assumption gives an equation in three of
    * the nine values we want to calculate.  8 more equations come from the
    * above routine as summarised at the top above (the chromaticity
    * calculation):
    *
    *    Given: color-x = color-X / (color-X + color-Y + color-Z)
    *    Hence: (color-x - 1)*color-X + color.x*color-Y + color.x*color-Z = 0
    *
    * This is 9 simultaneous equations in the 9 variables "color-C" and can be
    * solved by Cramer's rule.  Cramer's rule requires calculating 10 9x9 matrix
    * determinants, however this is not as bad as it seems because only 28 of
    * the total of 90 terms in the various matrices are non-zero.  Nevertheless
    * Cramer's rule is notoriously numerically unstable because the determinant
    * calculation involves the difference of large, but similar, numbers.  It is
    * difficult to be sure that the calculation is stable for real world values
    * and it is certain that it becomes unstable where the end points are close
    * together.
    *
    * So this code uses the perhaps slightly less optimal but more
    * understandable and totally obvious approach of calculating color-scale.
    *
    * This algorithm depends on the precision in white-scale and that is
    * (1/white-y), so we can immediately see that as white-y approaches 0 the
    * accuracy inherent in the cHRM chunk drops off substantially.
    *
    * libpng arithmetic: a simple inversion of the above equations
    * ------------------------------------------------------------
    *
    *    white_scale = 1/white-y
    *    white-X = white-x * white-scale
    *    white-Y = 1.0
    *    white-Z = (1 - white-x - white-y) * white_scale
    *
    *    white-C = red-C + green-C + blue-C
    *            = red-c*red-scale + green-c*green-scale + blue-c*blue-scale
    *
    * This gives us three equations in (red-scale,green-scale,blue-scale) where
    * all the coefficients are now known:
    *
    *    red-x*red-scale + green-x*green-scale + blue-x*blue-scale
    *       = white-x/white-y
    *    red-y*red-scale + green-y*green-scale + blue-y*blue-scale = 1
    *    red-z*red-scale + green-z*green-scale + blue-z*blue-scale
    *       = (1 - white-x - white-y)/white-y
    *
    * In the last equation color-z is (1 - color-x - color-y) so we can add all
    * three equations together to get an alternative third:
    *
    *    red-scale + green-scale + blue-scale = 1/white-y = white-scale
    *
    * So now we have a Cramer's rule solution where the determinants are just
    * 3x3 - far more tractible.  Unfortunately 3x3 determinants still involve
    * multiplication of three coefficients so we can't guarantee to avoid
    * overflow in the libpng fixed point representation.  Using Cramer's rule in
    * floating point is probably a good choice here, but it's not an option for
    * fixed point.  Instead proceed to simplify the first two equations by
    * eliminating what is likely to be the largest value, blue-scale:
    *
    *    blue-scale = white-scale - red-scale - green-scale
    *
    * Hence:
    *
    *    (red-x - blue-x)*red-scale + (green-x - blue-x)*green-scale =
    *                (white-x - blue-x)*white-scale
    *
    *    (red-y - blue-y)*red-scale + (green-y - blue-y)*green-scale =
    *                1 - blue-y*white-scale
    *
    * And now we can trivially solve for (red-scale,green-scale):
    *
    *    green-scale =
    *                (white-x - blue-x)*white-scale - (red-x - blue-x)*red-scale
    *                -----------------------------------------------------------
    *                                  green-x - blue-x
    *
    *    red-scale =
    *                1 - blue-y*white-scale - (green-y - blue-y) * green-scale
    *                ---------------------------------------------------------
    *                                  red-y - blue-y
    *
    * Hence:
    *
    *    red-scale =
    *          ( (green-x - blue-x) * (white-y - blue-y) -
    *            (green-y - blue-y) * (white-x - blue-x) ) / white-y
    * -------------------------------------------------------------------------
    *  (green-x - blue-x)*(red-y - blue-y)-(green-y - blue-y)*(red-x - blue-x)
    *
    *    green-scale =
    *          ( (red-y - blue-y) * (white-x - blue-x) -
    *            (red-x - blue-x) * (white-y - blue-y) ) / white-y
    * -------------------------------------------------------------------------
    *  (green-x - blue-x)*(red-y - blue-y)-(green-y - blue-y)*(red-x - blue-x)
    *
    * Accuracy:
    * The input values have 5 decimal digits of accuracy.  The values are all in
    * the range 0 < value < 1, so simple products are in the same range but may
    * need up to 10 decimal digits to preserve the original precision and avoid
    * underflow.  Because we are using a 32-bit signed representation we cannot
    * match this; the best is a little over 9 decimal digits, less than 10.
    *
    * The approach used here is to preserve the maximum precision within the
    * signed representation.  Because the red-scale calculation above uses the
    * difference between two products of values that must be in the range -1..+1
    * it is sufficient to divide the product by 7; ceil(100,000/32767*2).  The
    * factor is irrelevant in the calculation because it is applied to both
    * numerator and denominator.
    *
    * Note that the values of the differences of the products of the
    * chromaticities in the above equations tend to be small, for example for
    * the sRGB chromaticities they are:
    *
    * red numerator:    -0.04751
    * green numerator:  -0.08788
    * denominator:      -0.2241 (without white-y multiplication)
    *
    *  The resultant Y coefficients from the chromaticities of some widely used
    *  color space definitions are (to 15 decimal places):
    *
    *  sRGB
    *    0.212639005871510 0.715168678767756 0.072192315360734
    *  Kodak ProPhoto
    *    0.288071128229293 0.711843217810102 0.000085653960605
    *  Adobe RGB
    *    0.297344975250536 0.627363566255466 0.075291458493998
    *  Adobe Wide Gamut RGB
    *    0.258728243040113 0.724682314948566 0.016589442011321
    */
   /* By the argument, above overflow should be impossible here. The return
    * value of 2 indicates an internal error to the caller.
    */
   if (png_muldiv(&left, xy->greenx-xy->bluex, xy->redy - xy->bluey, 7) == 0)
      return 2;
   if (png_muldiv(&right, xy->greeny-xy->bluey, xy->redx - xy->bluex, 7) == 0)
      return 2;
   denominator = left - right;

   /* Now find the red numerator. */
   if (png_muldiv(&left, xy->greenx-xy->bluex, xy->whitey-xy->bluey, 7) == 0)
      return 2;
   if (png_muldiv(&right, xy->greeny-xy->bluey, xy->whitex-xy->bluex, 7) == 0)
      return 2;

   /* Overflow is possible here and it indicates an extreme set of PNG cHRM
    * chunk values.  This calculation actually returns the reciprocal of the
    * scale value because this allows us to delay the multiplication of white-y
    * into the denominator, which tends to produce a small number.
    */
   if (png_muldiv(&red_inverse, xy->whitey, denominator, left-right) == 0 ||
       red_inverse <= xy->whitey /* r+g+b scales = white scale */)
      return 1;

   /* Similarly for green_inverse: */
   if (png_muldiv(&left, xy->redy-xy->bluey, xy->whitex-xy->bluex, 7) == 0)
      return 2;
   if (png_muldiv(&right, xy->redx-xy->bluex, xy->whitey-xy->bluey, 7) == 0)
      return 2;
   if (png_muldiv(&green_inverse, xy->whitey, denominator, left-right) == 0 ||
       green_inverse <= xy->whitey)
      return 1;

   /* And the blue scale, the checks above guarantee this can't overflow but it
    * can still produce 0 for extreme cHRM values.
    */
   blue_scale = png_reciprocal(xy->whitey) - png_reciprocal(red_inverse) -
       png_reciprocal(green_inverse);
   if (blue_scale <= 0)
      return 1;


   /* And fill in the png_XYZ: */
   if (png_muldiv(&XYZ->red_X, xy->redx, PNG_FP_1, red_inverse) == 0)
      return 1;
   if (png_muldiv(&XYZ->red_Y, xy->redy, PNG_FP_1, red_inverse) == 0)
      return 1;
   if (png_muldiv(&XYZ->red_Z, PNG_FP_1 - xy->redx - xy->redy, PNG_FP_1,
       red_inverse) == 0)
      return 1;

   if (png_muldiv(&XYZ->green_X, xy->greenx, PNG_FP_1, green_inverse) == 0)
      return 1;
   if (png_muldiv(&XYZ->green_Y, xy->greeny, PNG_FP_1, green_inverse) == 0)
      return 1;
   if (png_muldiv(&XYZ->green_Z, PNG_FP_1 - xy->greenx - xy->greeny, PNG_FP_1,
       green_inverse) == 0)
      return 1;

   if (png_muldiv(&XYZ->blue_X, xy->bluex, blue_scale, PNG_FP_1) == 0)
      return 1;
   if (png_muldiv(&XYZ->blue_Y, xy->bluey, blue_scale, PNG_FP_1) == 0)
      return 1;
   if (png_muldiv(&XYZ->blue_Z, PNG_FP_1 - xy->bluex - xy->bluey, blue_scale,
       PNG_FP_1) == 0)
      return 1;

   return 0; /*success*/
}