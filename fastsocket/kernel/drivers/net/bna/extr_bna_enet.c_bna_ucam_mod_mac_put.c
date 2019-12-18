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
struct bna_ucam_mod {int /*<<< orphan*/  free_q; } ;
struct bna_mac {int /*<<< orphan*/  qe; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bna_ucam_mod_mac_put(struct bna_ucam_mod *ucam_mod, struct bna_mac *mac)
{
	list_add_tail(&mac->qe, &ucam_mod->free_q);
}