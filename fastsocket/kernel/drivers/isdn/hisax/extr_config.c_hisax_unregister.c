#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hisax_d_if {int /*<<< orphan*/  erq; TYPE_1__* cs; } ;
struct TYPE_4__ {scalar_t__ typ; } ;
struct TYPE_3__ {size_t cardnr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HiSax_closecard (size_t) ; 
 TYPE_2__* cards ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void hisax_unregister(struct hisax_d_if *hisax_d_if)
{
	cards[hisax_d_if->cs->cardnr].typ = 0;
	HiSax_closecard(hisax_d_if->cs->cardnr);
	skb_queue_purge(&hisax_d_if->erq);
}