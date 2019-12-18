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
struct ib_event {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_ib_event_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void rds_ib_cq_event_handler(struct ib_event *event, void *data)
{
	rdsdebug("event %u (%s) data %p\n",
		 event->event, rds_ib_event_str(event->event), data);
}