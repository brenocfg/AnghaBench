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
struct chsc_ssd_info {int path_mask; int /*<<< orphan*/ * chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  chp_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chp_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssd_register_chpids(struct chsc_ssd_info *ssd)
{
	int i;
	int mask;

	for (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (ssd->path_mask & mask)
			if (!chp_is_registered(ssd->chpid[i]))
				chp_new(ssd->chpid[i]);
	}
}