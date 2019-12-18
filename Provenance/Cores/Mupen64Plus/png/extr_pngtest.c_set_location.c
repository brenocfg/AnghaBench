#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct user_chunk_data {int* location; int /*<<< orphan*/ * info_ptr; } ;
typedef  int /*<<< orphan*/  png_structp ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_INFO_PLTE ; 
 int after_IDAT ; 
 int before_IDAT ; 
 int before_PLTE ; 
 scalar_t__ png_get_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_location(png_structp png_ptr, struct user_chunk_data *data, int what)
{
   int location;

   if ((data->location[0] & what) != 0 || (data->location[1] & what) != 0)
      return 0; /* already have one of these */

   /* Find where we are (the code below zeroes info_ptr to indicate that the
    * chunks before the first IDAT have been read.)
    */
   if (data->info_ptr == NULL) /* after IDAT */
      location = what | after_IDAT;

   else if (png_get_valid(png_ptr, data->info_ptr, PNG_INFO_PLTE) != 0)
      location = what | before_IDAT;

   else
      location = what | before_PLTE;

   if (data->location[0] == 0)
      data->location[0] = location;

   else
      data->location[1] = location;

   return 1; /* handled */
}