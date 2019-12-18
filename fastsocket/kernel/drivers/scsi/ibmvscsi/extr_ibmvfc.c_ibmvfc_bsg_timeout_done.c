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
struct ibmvfc_host {int /*<<< orphan*/  dev; scalar_t__ aborting_passthru; } ;
struct ibmvfc_event {struct ibmvfc_host* vhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 

__attribute__((used)) static void ibmvfc_bsg_timeout_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_host *vhost = evt->vhost;

	ibmvfc_free_event(evt);
	vhost->aborting_passthru = 0;
	dev_info(vhost->dev, "Passthru command cancelled\n");
}