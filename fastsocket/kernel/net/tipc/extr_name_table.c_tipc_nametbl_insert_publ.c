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
typedef  int /*<<< orphan*/  u32 ;
struct publication {int dummy; } ;
struct name_seq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * types; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct name_seq*,...) ; 
 size_t hash (int /*<<< orphan*/ ) ; 
 struct name_seq* nametbl_find_seq (int /*<<< orphan*/ ) ; 
 TYPE_1__ table ; 
 struct name_seq* tipc_nameseq_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct publication* tipc_nameseq_insert_publ (struct name_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct publication *tipc_nametbl_insert_publ(u32 type, u32 lower, u32 upper,
					     u32 scope, u32 node, u32 port, u32 key)
{
	struct name_seq *seq = nametbl_find_seq(type);

	dbg("tipc_nametbl_insert_publ: {%u,%u,%u} found %p\n", type, lower, upper, seq);
	if (lower > upper) {
		warn("Failed to publish illegal {%u,%u,%u}\n",
		     type, lower, upper);
		return NULL;
	}

	dbg("Publishing {%u,%u,%u} from 0x%x\n", type, lower, upper, node);
	if (!seq) {
		seq = tipc_nameseq_create(type, &table.types[hash(type)]);
		dbg("tipc_nametbl_insert_publ: created %p\n", seq);
	}
	if (!seq)
		return NULL;

	return tipc_nameseq_insert_publ(seq, type, lower, upper,
					scope, node, port, key);
}