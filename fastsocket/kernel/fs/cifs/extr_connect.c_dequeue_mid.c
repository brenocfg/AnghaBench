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
struct mid_q_entry {int /*<<< orphan*/  qhead; int /*<<< orphan*/  mid_state; int /*<<< orphan*/  when_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int /*<<< orphan*/  MID_RESPONSE_MALFORMED ; 
 int /*<<< orphan*/  MID_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
dequeue_mid(struct mid_q_entry *mid, bool malformed)
{
#ifdef CONFIG_CIFS_STATS2
	mid->when_received = jiffies;
#endif
	spin_lock(&GlobalMid_Lock);
	if (!malformed)
		mid->mid_state = MID_RESPONSE_RECEIVED;
	else
		mid->mid_state = MID_RESPONSE_MALFORMED;
	list_del_init(&mid->qhead);
	spin_unlock(&GlobalMid_Lock);
}