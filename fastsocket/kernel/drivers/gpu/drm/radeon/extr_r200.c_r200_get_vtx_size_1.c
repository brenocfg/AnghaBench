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

__attribute__((used)) static int r200_get_vtx_size_1(uint32_t vtx_fmt_1)
{
	int vtx_size, i, tex_size;
	vtx_size = 0;
	for (i = 0; i < 6; i++) {
		tex_size = (vtx_fmt_1 >> (i * 3)) & 0x7;
		if (tex_size > 4)
			continue;
		vtx_size += tex_size;
	}
	return vtx_size;
}