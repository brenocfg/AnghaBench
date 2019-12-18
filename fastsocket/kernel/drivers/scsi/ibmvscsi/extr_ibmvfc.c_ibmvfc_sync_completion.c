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
struct ibmvfc_event {int /*<<< orphan*/  comp; int /*<<< orphan*/ * xfer_iu; int /*<<< orphan*/ * sync_iu; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_sync_completion(struct ibmvfc_event *evt)
{
	/* copy the response back */
	if (evt->sync_iu)
		*evt->sync_iu = *evt->xfer_iu;

	complete(&evt->comp);
}