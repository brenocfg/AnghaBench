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
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_3__ {int /*<<< orphan*/  image_data; int /*<<< orphan*/ * info_ptr; int /*<<< orphan*/ * png_ptr; int /*<<< orphan*/  jmpbuf; } ;
typedef  TYPE_1__ mainprog_info ;

/* Variables and functions */
 int /*<<< orphan*/  png_destroy_write_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_row (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int writepng_encode_row(mainprog_info *mainprog_ptr)  /* NON-interlaced only! */
{
    png_structp png_ptr = (png_structp)mainprog_ptr->png_ptr;
    png_infop info_ptr = (png_infop)mainprog_ptr->info_ptr;


    /* as always, setjmp() must be called in every function that calls a
     * PNG-writing libpng function */

    if (setjmp(mainprog_ptr->jmpbuf)) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        mainprog_ptr->png_ptr = NULL;
        mainprog_ptr->info_ptr = NULL;
        return 2;
    }


    /* image_data points at our one row of image data */

    png_write_row(png_ptr, mainprog_ptr->image_data);

    return 0;
}