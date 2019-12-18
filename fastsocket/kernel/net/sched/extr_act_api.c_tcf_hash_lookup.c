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
typedef  scalar_t__ u32 ;
struct tcf_hashinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  hmask; struct tcf_common** htab; } ;
struct tcf_common {scalar_t__ tcfc_index; struct tcf_common* tcfc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ ) ; 
 size_t tcf_hash (scalar_t__,int /*<<< orphan*/ ) ; 

struct tcf_common *tcf_hash_lookup(u32 index, struct tcf_hashinfo *hinfo)
{
	struct tcf_common *p;

	read_lock_bh(hinfo->lock);
	for (p = hinfo->htab[tcf_hash(index, hinfo->hmask)]; p;
	     p = p->tcfc_next) {
		if (p->tcfc_index == index)
			break;
	}
	read_unlock_bh(hinfo->lock);

	return p;
}