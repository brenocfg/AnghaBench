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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct subscription {TYPE_1__ seq; } ;
struct name_seq {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * types; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct name_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t hash (int /*<<< orphan*/ ) ; 
 struct name_seq* nametbl_find_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_2__ table ; 
 struct name_seq* tipc_nameseq_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_nameseq_subscribe (struct name_seq*,struct subscription*) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_nametbl_subscribe(struct subscription *s)
{
	u32 type = s->seq.type;
	struct name_seq *seq;

	write_lock_bh(&tipc_nametbl_lock);
	seq = nametbl_find_seq(type);
	if (!seq) {
		seq = tipc_nameseq_create(type, &table.types[hash(type)]);
	}
	if (seq){
		spin_lock_bh(&seq->lock);
		dbg("tipc_nametbl_subscribe:found %p for {%u,%u,%u}\n",
		    seq, type, s->seq.lower, s->seq.upper);
		tipc_nameseq_subscribe(seq, s);
		spin_unlock_bh(&seq->lock);
	} else {
		warn("Failed to create subscription for {%u,%u,%u}\n",
		     s->seq.type, s->seq.lower, s->seq.upper);
	}
	write_unlock_bh(&tipc_nametbl_lock);
}