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
struct list_head {int dummy; } ;
struct bna_mcam_mod {int /*<<< orphan*/  free_handle_q; } ;
struct bna_mcam_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

struct bna_mcam_handle *
bna_mcam_mod_handle_get(struct bna_mcam_mod *mcam_mod)
{
	struct list_head *qe;

	if (list_empty(&mcam_mod->free_handle_q))
		return NULL;

	bfa_q_deq(&mcam_mod->free_handle_q, &qe);

	return (struct bna_mcam_handle *)qe;
}