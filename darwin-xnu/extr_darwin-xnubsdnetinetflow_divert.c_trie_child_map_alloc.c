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
typedef  int /*<<< orphan*/  uint16_t ;
struct flow_divert_trie {scalar_t__ child_maps_free_next; scalar_t__ child_maps_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TRIE_IDX ; 

__attribute__((used)) static uint16_t
trie_child_map_alloc(struct flow_divert_trie *trie)
{
	if (trie->child_maps_free_next < trie->child_maps_count) {
		return trie->child_maps_free_next++;
	} else {
		return NULL_TRIE_IDX;
	}
}