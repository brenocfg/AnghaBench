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
struct TYPE_2__ {scalar_t__ rbh_root; } ;
struct vm_map_header {TYPE_1__ rb_head_store; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SKIP_RB_TREE ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
vm_map_store_has_RB_support( struct vm_map_header *hdr )
{
	if ((void*)hdr->rb_head_store.rbh_root == (void*)(int)SKIP_RB_TREE) {
		return FALSE;
	}
	return TRUE;
}