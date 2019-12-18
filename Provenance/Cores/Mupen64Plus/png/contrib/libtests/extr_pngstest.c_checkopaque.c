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
struct TYPE_6__ {scalar_t__ warning_or_error; int /*<<< orphan*/  message; int /*<<< orphan*/ * opaque; } ;
struct TYPE_5__ {int opts; int /*<<< orphan*/  file_name; TYPE_2__ image; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int GBG_ERROR ; 
 int STRICT ; 
 int logerror (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  png_image_free (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
checkopaque(Image *image)
{
   if (image->image.opaque != NULL)
   {
      png_image_free(&image->image);
      return logerror(image, image->file_name, ": opaque not NULL", "");
   }

   /* Separate out the gamma+background_rgb_to_gray warning because it may
    * produce opaque component errors:
    */
   else if (image->image.warning_or_error != 0 &&
            (strcmp(image->image.message,
               "libpng does not support gamma+background+rgb_to_gray") == 0 ?
                  (image->opts & GBG_ERROR) != 0 : (image->opts & STRICT) != 0))
      return logerror(image, image->file_name, (image->opts & GBG_ERROR) != 0 ?
                      " --fault-gbg-warning" : " --strict", "");

   else
      return 1;
}