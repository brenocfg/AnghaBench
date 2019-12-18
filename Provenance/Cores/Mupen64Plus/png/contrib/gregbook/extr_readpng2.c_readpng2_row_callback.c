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
typedef  size_t png_uint_32 ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_bytep ;
struct TYPE_3__ {int pass; int /*<<< orphan*/  (* mainprog_display_row ) (size_t) ;int /*<<< orphan*/ * row_pointers; } ;
typedef  TYPE_1__ mainprog_info ;

/* Variables and functions */
 TYPE_1__* png_get_progressive_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_progressive_combine_row (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (size_t) ; 

__attribute__((used)) static void readpng2_row_callback(png_structp png_ptr, png_bytep new_row,
                                  png_uint_32 row_num, int pass)
{
    mainprog_info  *mainprog_ptr;


    /* first check whether the row differs from the previous pass; if not,
     * nothing to combine or display */

    if (!new_row)
        return;


    /* retrieve the pointer to our special-purpose struct so we can access
     * the old rows and image-display callback function */

    mainprog_ptr = png_get_progressive_ptr(png_ptr);


    /* save the pass number for optional use by the front end */

    mainprog_ptr->pass = pass;


    /* have libpng either combine the new row data with the existing row data
     * from previous passes (if interlaced) or else just copy the new row
     * into the main program's image buffer */

    png_progressive_combine_row(png_ptr, mainprog_ptr->row_pointers[row_num],
      new_row);


    /* finally, call the display routine in the main program with the number
     * of the row we just updated */

    (*mainprog_ptr->mainprog_display_row)(row_num);


    /* and we're ready for more */

    return;
}