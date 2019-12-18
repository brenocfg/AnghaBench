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
struct b43_wldev {struct b43_dfsentry* dfsentry; } ;
struct b43_txstatus_log {int end; struct b43_txstatus* log; } ;
struct b43_txstatus {int dummy; } ;
struct b43_dfsentry {struct b43_txstatus_log txstatlog; } ;

/* Variables and functions */
 int B43_NR_LOGGED_TXSTATUS ; 
 int /*<<< orphan*/  memcpy (struct b43_txstatus*,struct b43_txstatus const*,int) ; 

void b43_debugfs_log_txstat(struct b43_wldev *dev,
			    const struct b43_txstatus *status)
{
	struct b43_dfsentry *e = dev->dfsentry;
	struct b43_txstatus_log *log;
	struct b43_txstatus *cur;
	int i;

	if (!e)
		return;
	log = &e->txstatlog;
	i = log->end + 1;
	if (i == B43_NR_LOGGED_TXSTATUS)
		i = 0;
	log->end = i;
	cur = &(log->log[i]);
	memcpy(cur, status, sizeof(*cur));
}