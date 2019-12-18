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
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structp ;

/* Variables and functions */
 int /*<<< orphan*/  COL_FROM_ID (scalar_t__) ; 
 int /*<<< orphan*/  DEPTH_FROM_ID (scalar_t__) ; 
 scalar_t__ HEIGHT_FROM_ID (scalar_t__) ; 
 scalar_t__ transform_height (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static png_uint_32
standard_height(png_const_structp pp, png_uint_32 id)
{
   png_uint_32 height = HEIGHT_FROM_ID(id);

   if (height == 0)
      height = transform_height(pp, COL_FROM_ID(id), DEPTH_FROM_ID(id));

   return height;
}