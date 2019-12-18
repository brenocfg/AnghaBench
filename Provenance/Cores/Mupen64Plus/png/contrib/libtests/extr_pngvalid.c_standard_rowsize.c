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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structp ;

/* Variables and functions */
 int /*<<< orphan*/  COL_FROM_ID (int) ; 
 int /*<<< orphan*/  DEPTH_FROM_ID (int) ; 
 int bit_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int standard_width (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static png_uint_32
standard_rowsize(png_const_structp pp, png_uint_32 id)
{
   png_uint_32 width = standard_width(pp, id);

   /* This won't overflow: */
   width *= bit_size(pp, COL_FROM_ID(id), DEPTH_FROM_ID(id));
   return (width + 7) / 8;
}