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
 scalar_t__ TYPE_MDA ; 
 int /*<<< orphan*/  VGA_MAP_MEM (int,int) ; 
 int /*<<< orphan*/  mda_detect () ; 
 int mda_gfx_port ; 
 int mda_index_port ; 
 int /*<<< orphan*/  mda_initialize () ; 
 int mda_mode_port ; 
 int mda_num_columns ; 
 int mda_num_lines ; 
 int /*<<< orphan*/  mda_set_cursor (int) ; 
 int mda_status_port ; 
 scalar_t__ mda_type ; 
 char* mda_type_name ; 
 int mda_value_port ; 
 int /*<<< orphan*/  mda_vram_base ; 
 int mda_vram_len ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static const char *mdacon_startup(void)
{
	mda_num_columns = 80;
	mda_num_lines   = 25;

	mda_vram_len  = 0x01000;
	mda_vram_base = VGA_MAP_MEM(0xb0000, mda_vram_len);

	mda_index_port  = 0x3b4;
	mda_value_port  = 0x3b5;
	mda_mode_port   = 0x3b8;
	mda_status_port = 0x3ba;
	mda_gfx_port    = 0x3bf;

	mda_type = TYPE_MDA;
	mda_type_name = "MDA";

	if (! mda_detect()) {
		printk("mdacon: MDA card not detected.\n");
		return NULL;
	}

	if (mda_type != TYPE_MDA) {
		mda_initialize();
	}

	/* cursor looks ugly during boot-up, so turn it off */
	mda_set_cursor(mda_vram_len - 1);

	printk("mdacon: %s with %ldK of memory detected.\n",
		mda_type_name, mda_vram_len/1024);

	return "MDA-2";
}