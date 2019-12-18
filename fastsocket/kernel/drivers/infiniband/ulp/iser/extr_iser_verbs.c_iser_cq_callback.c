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
struct iser_device {int /*<<< orphan*/ * cq_tasklet; } ;
struct iser_cq_desc {int cq_index; struct iser_device* device; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_cq_callback(struct ib_cq *cq, void *cq_context)
{
	struct iser_cq_desc *cq_desc = (struct iser_cq_desc *)cq_context;
	struct iser_device  *device = cq_desc->device;
	int cq_index = cq_desc->cq_index;

	tasklet_schedule(&device->cq_tasklet[cq_index]);
}