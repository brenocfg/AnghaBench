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
typedef  scalar_t__ png_structp ;
typedef  scalar_t__ png_infop ;
struct TYPE_3__ {int /*<<< orphan*/  info_ptr; int /*<<< orphan*/  png_ptr; } ;
typedef  TYPE_1__ mainprog_info ;

/* Variables and functions */
 int /*<<< orphan*/  png_destroy_write_struct (scalar_t__*,scalar_t__*) ; 

void writepng_cleanup(mainprog_info *mainprog_ptr)
{
    png_structp png_ptr = (png_structp)mainprog_ptr->png_ptr;
    png_infop info_ptr = (png_infop)mainprog_ptr->info_ptr;

    if (png_ptr && info_ptr)
        png_destroy_write_struct(&png_ptr, &info_ptr);
}