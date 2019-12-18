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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISPC_CONFIG ; 
 int DISPC_LOAD_CLUT_ONCE_FRAME ; 
 int DISPC_LOAD_CLUT_ONLY ; 
 int DISPC_LOAD_FRAME_ONLY ; 
 int /*<<< orphan*/  MOD_REG_FLD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_load_mode(int mode)
{
	BUG_ON(mode & ~(DISPC_LOAD_CLUT_ONLY | DISPC_LOAD_FRAME_ONLY |
			DISPC_LOAD_CLUT_ONCE_FRAME));
	MOD_REG_FLD(DISPC_CONFIG, 0x03 << 1, mode << 1);
}