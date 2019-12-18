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
struct hpsb_iso {int /*<<< orphan*/  (* callback ) (struct hpsb_iso*) ;int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hpsb_iso*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hpsb_iso_wake(struct hpsb_iso *iso)
{
	wake_up_interruptible(&iso->waitq);

	if (iso->callback)
		iso->callback(iso);
}