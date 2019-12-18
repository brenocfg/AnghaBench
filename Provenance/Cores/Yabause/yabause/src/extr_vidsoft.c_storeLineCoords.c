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
typedef  int /*<<< orphan*/  vdp1cmd_struct ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Vdp1 ;

/* Variables and functions */

__attribute__((used)) static int
storeLineCoords(int x, int y, int i, void *arrays, Vdp1* regs, vdp1cmd_struct * cmd, u8* ram, u8* back_framebuffer) {
	int **intArrays = arrays;

	intArrays[0][i] = x;
	intArrays[1][i] = y;

	return 0;
}