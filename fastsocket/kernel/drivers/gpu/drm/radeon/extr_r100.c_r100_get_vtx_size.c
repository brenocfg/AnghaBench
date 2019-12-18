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
typedef  int uint32_t ;

/* Variables and functions */
 int RADEON_SE_VTX_FMT_FPALPHA ; 
 int RADEON_SE_VTX_FMT_FPCOLOR ; 
 int RADEON_SE_VTX_FMT_FPFOG ; 
 int RADEON_SE_VTX_FMT_FPSPEC ; 
 int RADEON_SE_VTX_FMT_N0 ; 
 int RADEON_SE_VTX_FMT_N1 ; 
 int RADEON_SE_VTX_FMT_PKCOLOR ; 
 int RADEON_SE_VTX_FMT_PKSPEC ; 
 int RADEON_SE_VTX_FMT_Q0 ; 
 int RADEON_SE_VTX_FMT_Q1 ; 
 int RADEON_SE_VTX_FMT_Q2 ; 
 int RADEON_SE_VTX_FMT_Q3 ; 
 int RADEON_SE_VTX_FMT_ST0 ; 
 int RADEON_SE_VTX_FMT_ST1 ; 
 int RADEON_SE_VTX_FMT_ST2 ; 
 int RADEON_SE_VTX_FMT_ST3 ; 
 int RADEON_SE_VTX_FMT_W0 ; 
 int RADEON_SE_VTX_FMT_W1 ; 
 int RADEON_SE_VTX_FMT_XY1 ; 
 int RADEON_SE_VTX_FMT_Z ; 
 int RADEON_SE_VTX_FMT_Z1 ; 

__attribute__((used)) static int r100_get_vtx_size(uint32_t vtx_fmt)
{
	int vtx_size;
	vtx_size = 2;
	/* ordered according to bits in spec */
	if (vtx_fmt & RADEON_SE_VTX_FMT_W0)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_FPCOLOR)
		vtx_size += 3;
	if (vtx_fmt & RADEON_SE_VTX_FMT_FPALPHA)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_PKCOLOR)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_FPSPEC)
		vtx_size += 3;
	if (vtx_fmt & RADEON_SE_VTX_FMT_FPFOG)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_PKSPEC)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_ST0)
		vtx_size += 2;
	if (vtx_fmt & RADEON_SE_VTX_FMT_ST1)
		vtx_size += 2;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Q1)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_ST2)
		vtx_size += 2;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Q2)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_ST3)
		vtx_size += 2;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Q3)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Q0)
		vtx_size++;
	/* blend weight */
	if (vtx_fmt & (0x7 << 15))
		vtx_size += (vtx_fmt >> 15) & 0x7;
	if (vtx_fmt & RADEON_SE_VTX_FMT_N0)
		vtx_size += 3;
	if (vtx_fmt & RADEON_SE_VTX_FMT_XY1)
		vtx_size += 2;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Z1)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_W1)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_N1)
		vtx_size++;
	if (vtx_fmt & RADEON_SE_VTX_FMT_Z)
		vtx_size++;
	return vtx_size;
}