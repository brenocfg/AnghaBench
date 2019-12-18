#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int png_fixed_point ;
typedef  TYPE_1__* png_const_structrp ;
typedef  char* png_const_charp ;
typedef  TYPE_2__* png_colorspacerp ;
struct TYPE_9__ {int flags; int gamma; } ;
struct TYPE_8__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_CHUNK_WRITE_ERROR ; 
 int PNG_COLORSPACE_FROM_gAMA ; 
 int PNG_COLORSPACE_HAVE_GAMMA ; 
 int PNG_COLORSPACE_INVALID ; 
 int PNG_IS_READ_STRUCT ; 
 int /*<<< orphan*/  png_chunk_report (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_colorspace_check_gamma (TYPE_1__*,TYPE_2__*,int,int) ; 

void /* PRIVATE */
png_colorspace_set_gamma(png_const_structrp png_ptr,
    png_colorspacerp colorspace, png_fixed_point gAMA)
{
   /* Changed in libpng-1.5.4 to limit the values to ensure overflow can't
    * occur.  Since the fixed point representation is asymetrical it is
    * possible for 1/gamma to overflow the limit of 21474 and this means the
    * gamma value must be at least 5/100000 and hence at most 20000.0.  For
    * safety the limits here are a little narrower.  The values are 0.00016 to
    * 6250.0, which are truly ridiculous gamma values (and will produce
    * displays that are all black or all white.)
    *
    * In 1.6.0 this test replaces the ones in pngrutil.c, in the gAMA chunk
    * handling code, which only required the value to be >0.
    */
   png_const_charp errmsg;

   if (gAMA < 16 || gAMA > 625000000)
      errmsg = "gamma value out of range";

#  ifdef PNG_READ_gAMA_SUPPORTED
   /* Allow the application to set the gamma value more than once */
   else if ((png_ptr->mode & PNG_IS_READ_STRUCT) != 0 &&
      (colorspace->flags & PNG_COLORSPACE_FROM_gAMA) != 0)
      errmsg = "duplicate";
#  endif

   /* Do nothing if the colorspace is already invalid */
   else if ((colorspace->flags & PNG_COLORSPACE_INVALID) != 0)
      return;

   else
   {
      if (png_colorspace_check_gamma(png_ptr, colorspace, gAMA,
          1/*from gAMA*/) != 0)
      {
         /* Store this gamma value. */
         colorspace->gamma = gAMA;
         colorspace->flags |=
            (PNG_COLORSPACE_HAVE_GAMMA | PNG_COLORSPACE_FROM_gAMA);
      }

      /* At present if the check_gamma test fails the gamma of the colorspace is
       * not updated however the colorspace is not invalidated.  This
       * corresponds to the case where the existing gamma comes from an sRGB
       * chunk or profile.  An error message has already been output.
       */
      return;
   }

   /* Error exit - errmsg has been set. */
   colorspace->flags |= PNG_COLORSPACE_INVALID;
   png_chunk_report(png_ptr, errmsg, PNG_CHUNK_WRITE_ERROR);
}