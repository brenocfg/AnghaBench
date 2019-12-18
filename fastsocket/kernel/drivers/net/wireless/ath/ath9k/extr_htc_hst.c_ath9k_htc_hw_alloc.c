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
struct htc_target {int /*<<< orphan*/  tgt_ready; struct htc_endpoint* endpoint; struct device* dev; void* hif_dev; struct ath9k_htc_hif* hif; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  target_wait; } ;
struct htc_endpoint {int /*<<< orphan*/  dl_pipeid; int /*<<< orphan*/  ul_pipeid; } ;
struct device {int dummy; } ;
struct ath9k_htc_hif {int /*<<< orphan*/  control_dl_pipe; int /*<<< orphan*/  control_ul_pipe; } ;

/* Variables and functions */
 size_t ENDPOINT0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct htc_target* kzalloc (int,int /*<<< orphan*/ ) ; 

struct htc_target *ath9k_htc_hw_alloc(void *hif_handle,
				      struct ath9k_htc_hif *hif,
				      struct device *dev)
{
	struct htc_endpoint *endpoint;
	struct htc_target *target;

	target = kzalloc(sizeof(struct htc_target), GFP_KERNEL);
	if (!target)
		return NULL;

	init_completion(&target->target_wait);
	init_completion(&target->cmd_wait);

	target->hif = hif;
	target->hif_dev = hif_handle;
	target->dev = dev;

	/* Assign control endpoint pipe IDs */
	endpoint = &target->endpoint[ENDPOINT0];
	endpoint->ul_pipeid = hif->control_ul_pipe;
	endpoint->dl_pipeid = hif->control_dl_pipe;

	atomic_set(&target->tgt_ready, 0);

	return target;
}