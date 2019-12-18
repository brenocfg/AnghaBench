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
struct jffs2_raw_node_ref {struct jffs2_raw_node_ref* next_in_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_noderef (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_obsolete (struct jffs2_raw_node_ref*) ; 
 int /*<<< orphan*/  ref_offset (struct jffs2_raw_node_ref*) ; 

__attribute__((used)) static struct jffs2_raw_node_ref *jffs2_first_valid_node(struct jffs2_raw_node_ref *ref)
{
	while (ref && ref->next_in_ino) {
		if (!ref_obsolete(ref))
			return ref;
		dbg_noderef("node at 0x%08x is obsoleted. Ignoring.\n", ref_offset(ref));
		ref = ref->next_in_ino;
	}
	return NULL;
}