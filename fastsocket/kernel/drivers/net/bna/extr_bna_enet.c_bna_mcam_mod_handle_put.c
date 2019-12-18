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
struct bna_mcam_mod {int /*<<< orphan*/  free_handle_q; } ;
struct bna_mcam_handle {int /*<<< orphan*/  qe; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bna_mcam_mod_handle_put(struct bna_mcam_mod *mcam_mod,
			struct bna_mcam_handle *handle)
{
	list_add_tail(&handle->qe, &mcam_mod->free_handle_q);
}