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
struct jffs2_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ jffs2_cleanmarker_oob (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_dataflash (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_dataflash_cleanup (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_nand_flash_cleanup (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_nor_wbuf_flash (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_nor_wbuf_flash_cleanup (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_ubivol (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_ubivol_cleanup (struct jffs2_sb_info*) ; 

void jffs2_flash_cleanup(struct jffs2_sb_info *c) {

	if (jffs2_cleanmarker_oob(c)) {
		jffs2_nand_flash_cleanup(c);
	}

	/* and DataFlash */
	if (jffs2_dataflash(c)) {
		jffs2_dataflash_cleanup(c);
	}

	/* and Intel "Sibley" flash */
	if (jffs2_nor_wbuf_flash(c)) {
		jffs2_nor_wbuf_flash_cleanup(c);
	}

	/* and an UBI volume */
	if (jffs2_ubivol(c)) {
		jffs2_ubivol_cleanup(c);
	}
}