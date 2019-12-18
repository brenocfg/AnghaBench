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
struct TYPE_3__ {int /*<<< orphan*/  (* mainprog_finish_display ) () ;} ;
typedef  TYPE_1__ mainprog_info ;

/* Variables and functions */
 TYPE_1__* png_get_progressive_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void readpng2_end_callback(png_structp png_ptr, png_infop info_ptr)
{
    mainprog_info  *mainprog_ptr;


    /* retrieve the pointer to our special-purpose struct */

    mainprog_ptr = png_get_progressive_ptr(png_ptr);


    /* let the main program know that it should flush any buffered image
     * data to the display now and set a "done" flag or whatever, but note
     * that it SHOULD NOT DESTROY THE PNG STRUCTS YET--in other words, do
     * NOT call readpng2_cleanup() either here or in the finish_display()
     * routine; wait until control returns to the main program via
     * readpng2_decode_data() */

    (*mainprog_ptr->mainprog_finish_display)();


    /* all done */

    (void)info_ptr; /* Unused */

    return;
}