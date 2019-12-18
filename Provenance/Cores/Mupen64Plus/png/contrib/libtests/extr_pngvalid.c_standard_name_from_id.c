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
typedef  int /*<<< orphan*/  png_uint_32 ;

/* Variables and functions */
 int /*<<< orphan*/  COL_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPTH_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_INTERLACE_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEIGHT_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERLACE_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PALETTE_FROM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIDTH_FROM_ID (int /*<<< orphan*/ ) ; 
 size_t standard_name (char*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
standard_name_from_id(char *buffer, size_t bufsize, size_t pos, png_uint_32 id)
{
   return standard_name(buffer, bufsize, pos, COL_FROM_ID(id),
      DEPTH_FROM_ID(id), PALETTE_FROM_ID(id), INTERLACE_FROM_ID(id),
      WIDTH_FROM_ID(id), HEIGHT_FROM_ID(id), DO_INTERLACE_FROM_ID(id));
}