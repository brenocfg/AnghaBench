#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int device_add_pending; int mfc_pfc; } ;
struct pcmcia_socket {int /*<<< orphan*/  device_add; TYPE_1__ pcmcia_state; int /*<<< orphan*/  sock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_dev_dbg (int,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcmcia_add_device_later(struct pcmcia_socket *s, int mfc)
{
	if (!s->pcmcia_state.device_add_pending) {
		ds_dev_dbg(1, &s->dev, "scheduling to add %s secondary"
		       " device to %d\n", mfc ? "mfc" : "pfc", s->sock);
		s->pcmcia_state.device_add_pending = 1;
		s->pcmcia_state.mfc_pfc = mfc;
		schedule_work(&s->device_add);
	}
	return;
}