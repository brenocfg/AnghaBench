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
typedef  void* u32 ;
struct hda_bus_unsolicited {int wp; int /*<<< orphan*/  work; void** queue; } ;
struct hda_bus {int /*<<< orphan*/  workq; struct hda_bus_unsolicited* unsol; } ;

/* Variables and functions */
 int HDA_UNSOL_QUEUE_SIZE ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hda_unsol_event (struct hda_bus*,void*,void*) ; 

int snd_hda_queue_unsol_event(struct hda_bus *bus, u32 res, u32 res_ex)
{
	struct hda_bus_unsolicited *unsol;
	unsigned int wp;

	if (!bus || !bus->workq)
		return 0;

	trace_hda_unsol_event(bus, res, res_ex);
	unsol = bus->unsol;
	if (!unsol)
		return 0;

	wp = (unsol->wp + 1) % HDA_UNSOL_QUEUE_SIZE;
	unsol->wp = wp;

	wp <<= 1;
	unsol->queue[wp] = res;
	unsol->queue[wp + 1] = res_ex;

	queue_work(bus->workq, &unsol->work);

	return 0;
}