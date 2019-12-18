#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int /*<<< orphan*/  fs16 ;
typedef  int /*<<< orphan*/  befs_btree_nodehead ;
struct TYPE_4__ {int all_key_length; } ;
struct TYPE_5__ {scalar_t__ od_node; TYPE_1__ head; } ;
typedef  TYPE_2__ befs_btree_node ;

/* Variables and functions */

__attribute__((used)) static fs16 *
befs_bt_keylen_index(befs_btree_node * node)
{
	const int keylen_align = 8;
	unsigned long int off =
	    (sizeof (befs_btree_nodehead) + node->head.all_key_length);
	ulong tmp = off % keylen_align;

	if (tmp)
		off += keylen_align - tmp;

	return (fs16 *) ((void *) node->od_node + off);
}