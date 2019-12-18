#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* image; size_t cb_image; } ;
typedef  TYPE_1__ png_store ;
typedef  int /*<<< orphan*/ * png_const_structp ;
typedef  int* png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  store_log (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
store_image_free(png_store *ps, png_const_structp pp)
{
   if (ps->image != NULL)
   {
      png_bytep image = ps->image;

      if (image[-1] != 0xed || image[ps->cb_image] != 0xfe)
      {
         if (pp != NULL)
            png_error(pp, "png_store image overwrite (1)");
         else
            store_log(ps, NULL, "png_store image overwrite (2)", 1);
      }

      ps->image = NULL;
      ps->cb_image = 0;
      --image;
      free(image);
   }
}