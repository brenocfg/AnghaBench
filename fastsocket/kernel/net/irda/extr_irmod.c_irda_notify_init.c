#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * instance; int /*<<< orphan*/ * status_indication; int /*<<< orphan*/ * flow_indication; int /*<<< orphan*/ * disconnect_indication; int /*<<< orphan*/ * connect_indication; int /*<<< orphan*/ * connect_confirm; int /*<<< orphan*/ * udata_indication; int /*<<< orphan*/ * data_indication; } ;
typedef  TYPE_1__ notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

void irda_notify_init(notify_t *notify)
{
	notify->data_indication = NULL;
	notify->udata_indication = NULL;
	notify->connect_confirm = NULL;
	notify->connect_indication = NULL;
	notify->disconnect_indication = NULL;
	notify->flow_indication = NULL;
	notify->status_indication = NULL;
	notify->instance = NULL;
	strlcpy(notify->name, "Unknown", sizeof(notify->name));
}