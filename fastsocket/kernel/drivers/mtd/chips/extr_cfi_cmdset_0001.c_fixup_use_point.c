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
struct mtd_info {int /*<<< orphan*/  unpoint; scalar_t__ point; struct map_info* priv; } ;
struct map_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ cfi_intelext_point ; 
 int /*<<< orphan*/  cfi_intelext_unpoint ; 
 scalar_t__ map_is_linear (struct map_info*) ; 

__attribute__((used)) static void fixup_use_point(struct mtd_info *mtd, void *param)
{
	struct map_info *map = mtd->priv;
	if (!mtd->point && map_is_linear(map)) {
		mtd->point   = cfi_intelext_point;
		mtd->unpoint = cfi_intelext_unpoint;
	}
}