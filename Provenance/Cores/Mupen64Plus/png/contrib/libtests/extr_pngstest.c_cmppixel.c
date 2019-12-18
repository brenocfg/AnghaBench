#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  void* png_uint_16 ;
typedef  int /*<<< orphan*/  png_const_voidp ;
typedef  char* png_const_charp ;
struct TYPE_16__ {int* error; scalar_t__ in_opaque; scalar_t__ accumulate; scalar_t__ output_8bit; int /*<<< orphan*/  (* out_gp ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* from_linear ) (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  background; int /*<<< orphan*/  (* transform ) (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* in_gp ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Transform ;
struct TYPE_17__ {scalar_t__ a; scalar_t__ r; scalar_t__ g; scalar_t__ b; } ;
typedef  TYPE_2__ Pixel ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int logpixel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmppixel(Transform *transform, png_const_voidp in, png_const_voidp out,
   png_uint_32 x, png_uint_32 y/*or palette index*/)
{
   int maxerr;
   png_const_charp errmsg;
   Pixel pixel_in, pixel_calc, pixel_out;

   transform->in_gp(&pixel_in, in);

   if (transform->from_linear == NULL)
      transform->transform(&pixel_calc, &pixel_in, transform->background);

   else
   {
      transform->transform(&pixel_out, &pixel_in, transform->background);
      transform->from_linear(&pixel_calc, &pixel_out, NULL);
   }

   transform->out_gp(&pixel_out, out);

   /* Eliminate the case where the input and output values match exactly. */
   if (pixel_calc.a == pixel_out.a && pixel_calc.r == pixel_out.r &&
      pixel_calc.g == pixel_out.g && pixel_calc.b == pixel_out.b)
      return 1;

   /* Eliminate the case where the output pixel is transparent and the output
    * is 8-bit - any component values are valid.  Don't check the input alpha
    * here to also skip the 16-bit small alpha cases.
    */
   if (transform->output_8bit && pixel_calc.a == 0 && pixel_out.a == 0)
      return 1;

   /* Check for alpha errors first; an alpha error can damage the components too
    * so avoid spurious checks on components if one is found.
    */
   errmsg = NULL;
   {
      int err_a = abs(pixel_calc.a-pixel_out.a);

      if (err_a > transform->error[3])
      {
         /* If accumulating check the components too */
         if (transform->accumulate)
            transform->error[3] = (png_uint_16)err_a;

         else
            errmsg = "alpha";
      }
   }

   /* Now if *either* of the output alphas are 0 but alpha is within tolerance
    * eliminate the 8-bit component comparison.
    */
   if (errmsg == NULL && transform->output_8bit &&
      (pixel_calc.a == 0 || pixel_out.a == 0))
      return 1;

   if (errmsg == NULL) /* else just signal an alpha error */
   {
      int err_r = abs(pixel_calc.r - pixel_out.r);
      int err_g = abs(pixel_calc.g - pixel_out.g);
      int err_b = abs(pixel_calc.b - pixel_out.b);
      int limit;

      if ((err_r | err_g | err_b) == 0)
         return 1; /* exact match */

      /* Mismatch on a component, check the input alpha */
      if (pixel_in.a >= transform->in_opaque)
      {
         errmsg = "opaque component";
         limit = 2; /* opaque */
      }

      else if (pixel_in.a > 0)
      {
         errmsg = "alpha component";
         limit = 1; /* partially transparent */
      }

      else
      {
         errmsg = "transparent component (background)";
         limit = 0; /* transparent */
      }

      maxerr = err_r;
      if (maxerr < err_g) maxerr = err_g;
      if (maxerr < err_b) maxerr = err_b;

      if (maxerr <= transform->error[limit])
         return 1; /* within the error limits */

      /* Handle a component mis-match; log it, just return an error code, or
       * accumulate it.
       */
      if (transform->accumulate)
      {
         transform->error[limit] = (png_uint_16)maxerr;
         return 1; /* to cause the caller to keep going */
      }
   }

   /* Failure to match and not accumulating, so the error must be logged. */
   return logpixel(transform, x, y, &pixel_in, &pixel_calc, &pixel_out, errmsg);
}