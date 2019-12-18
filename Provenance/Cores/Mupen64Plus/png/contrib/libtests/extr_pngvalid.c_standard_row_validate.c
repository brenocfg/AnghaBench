#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ps; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ standard_display ;
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int STANDARD_ROWMAX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int pixel_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_row (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * store_image_row (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void
standard_row_validate(standard_display *dp, png_const_structp pp,
   int iImage, int iDisplay, png_uint_32 y)
{
   int where;
   png_byte std[STANDARD_ROWMAX];

   /* The row must be pre-initialized to the magic number here for the size
    * tests to pass:
    */
   memset(std, 178, sizeof std);
   standard_row(pp, std, dp->id, y);

   /* At the end both the 'row' and 'display' arrays should end up identical.
    * In earlier passes 'row' will be partially filled in, with only the pixels
    * that have been read so far, but 'display' will have those pixels
    * replicated to fill the unread pixels while reading an interlaced image.
    */
   if (iImage >= 0 &&
      (where = pixel_cmp(std, store_image_row(dp->ps, pp, iImage, y),
            dp->bit_width)) != 0)
   {
      char msg[64];
      sprintf(msg, "PNG image row[%lu][%d] changed from %.2x to %.2x",
         (unsigned long)y, where-1, std[where-1],
         store_image_row(dp->ps, pp, iImage, y)[where-1]);
      png_error(pp, msg);
   }

   if (iDisplay >= 0 &&
      (where = pixel_cmp(std, store_image_row(dp->ps, pp, iDisplay, y),
         dp->bit_width)) != 0)
   {
      char msg[64];
      sprintf(msg, "display row[%lu][%d] changed from %.2x to %.2x",
         (unsigned long)y, where-1, std[where-1],
         store_image_row(dp->ps, pp, iDisplay, y)[where-1]);
      png_error(pp, msg);
   }
}