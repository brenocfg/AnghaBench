#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_const_structrp ;
typedef  int png_byte ;
struct TYPE_5__ {int mode; } ;

/* Variables and functions */
 int PNG_AFTER_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_IS_READ_STRUCT ; 
 int /*<<< orphan*/  png_app_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 

__attribute__((used)) static png_byte
check_location(png_const_structrp png_ptr, int location)
{
   location &= (PNG_HAVE_IHDR|PNG_HAVE_PLTE|PNG_AFTER_IDAT);

   /* New in 1.6.0; copy the location and check it.  This is an API
    * change; previously the app had to use the
    * png_set_unknown_chunk_location API below for each chunk.
    */
   if (location == 0 && (png_ptr->mode & PNG_IS_READ_STRUCT) == 0)
   {
      /* Write struct, so unknown chunks come from the app */
      png_app_warning(png_ptr,
          "png_set_unknown_chunks now expects a valid location");
      /* Use the old behavior */
      location = (png_byte)(png_ptr->mode &
          (PNG_HAVE_IHDR|PNG_HAVE_PLTE|PNG_AFTER_IDAT));
   }

   /* This need not be an internal error - if the app calls
    * png_set_unknown_chunks on a read pointer it must get the location right.
    */
   if (location == 0)
      png_error(png_ptr, "invalid location in png_set_unknown_chunks");

   /* Now reduce the location to the top-most set bit by removing each least
    * significant bit in turn.
    */
   while (location != (location & -location))
      location &= ~(location & -location);

   /* The cast is safe because 'location' is a bit mask and only the low four
    * bits are significant.
    */
   return (png_byte)location;
}