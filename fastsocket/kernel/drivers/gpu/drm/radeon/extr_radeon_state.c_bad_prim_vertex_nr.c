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

/* Variables and functions */
#define  RADEON_PRIM_TYPE_3VRT_LINE_LIST 137 
#define  RADEON_PRIM_TYPE_3VRT_POINT_LIST 136 
#define  RADEON_PRIM_TYPE_LINE 135 
#define  RADEON_PRIM_TYPE_LINE_STRIP 134 
 int RADEON_PRIM_TYPE_MASK ; 
#define  RADEON_PRIM_TYPE_NONE 133 
#define  RADEON_PRIM_TYPE_POINT 132 
#define  RADEON_PRIM_TYPE_RECT_LIST 131 
#define  RADEON_PRIM_TYPE_TRI_FAN 130 
#define  RADEON_PRIM_TYPE_TRI_LIST 129 
#define  RADEON_PRIM_TYPE_TRI_STRIP 128 

__attribute__((used)) static int bad_prim_vertex_nr(int primitive, int nr)
{
	switch (primitive & RADEON_PRIM_TYPE_MASK) {
	case RADEON_PRIM_TYPE_NONE:
	case RADEON_PRIM_TYPE_POINT:
		return nr < 1;
	case RADEON_PRIM_TYPE_LINE:
		return (nr & 1) || nr == 0;
	case RADEON_PRIM_TYPE_LINE_STRIP:
		return nr < 2;
	case RADEON_PRIM_TYPE_TRI_LIST:
	case RADEON_PRIM_TYPE_3VRT_POINT_LIST:
	case RADEON_PRIM_TYPE_3VRT_LINE_LIST:
	case RADEON_PRIM_TYPE_RECT_LIST:
		return nr % 3 || nr == 0;
	case RADEON_PRIM_TYPE_TRI_FAN:
	case RADEON_PRIM_TYPE_TRI_STRIP:
		return nr < 3;
	default:
		return 1;
	}
}