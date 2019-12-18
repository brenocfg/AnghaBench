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
typedef  int /*<<< orphan*/  ulg ;
typedef  int /*<<< orphan*/  uch ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_3__ {int /*<<< orphan*/ * info_ptr; int /*<<< orphan*/ * png_ptr; int /*<<< orphan*/  jmpbuf; } ;
typedef  TYPE_1__ mainprog_info ;

/* Variables and functions */
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_process_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int readpng2_decode_data(mainprog_info *mainprog_ptr, uch *rawbuf, ulg length)
{
    png_structp png_ptr = (png_structp)mainprog_ptr->png_ptr;
    png_infop info_ptr = (png_infop)mainprog_ptr->info_ptr;


    /* setjmp() must be called in every function that calls a PNG-reading
     * libpng function */

    if (setjmp(mainprog_ptr->jmpbuf)) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        mainprog_ptr->png_ptr = NULL;
        mainprog_ptr->info_ptr = NULL;
        return 2;
    }


    /* hand off the next chunk of input data to libpng for decoding */

    png_process_data(png_ptr, info_ptr, rawbuf, length);

    return 0;
}