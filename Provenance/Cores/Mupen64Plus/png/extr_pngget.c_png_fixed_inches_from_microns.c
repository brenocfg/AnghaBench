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
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  int /*<<< orphan*/  png_const_structrp ;

/* Variables and functions */
 int /*<<< orphan*/  png_muldiv_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static png_fixed_point
png_fixed_inches_from_microns(png_const_structrp png_ptr, png_int_32 microns)
{
   /* Convert from metres * 1,000,000 to inches * 100,000, meters to
    * inches is simply *(100/2.54), so we want *(10/2.54) == 500/127.
    * Notice that this can overflow - a warning is output and 0 is
    * returned.
    */
   return png_muldiv_warn(png_ptr, microns, 500, 127);
}