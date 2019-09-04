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
typedef  char uint8_t ;
typedef  scalar_t__ uint16_t ;
struct flow_divert_trie {scalar_t__ root; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ length; scalar_t__ child_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLE_WEBCLIP_ID_PREFIX ; 
 scalar_t__ NULL_TRIE_IDX ; 
 char TRIE_BYTE (struct flow_divert_trie*,scalar_t__) ; 
 scalar_t__ TRIE_CHILD (struct flow_divert_trie*,scalar_t__,char) ; 
 TYPE_1__ TRIE_NODE (struct flow_divert_trie*,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint16_t
flow_divert_trie_search(struct flow_divert_trie *trie, uint8_t *string_bytes)
{
	uint16_t current = trie->root;
	uint16_t string_idx = 0;

	while (current != NULL_TRIE_IDX) {
		uint16_t next = NULL_TRIE_IDX;
		uint16_t node_end = TRIE_NODE(trie, current).start + TRIE_NODE(trie, current).length;
		uint16_t node_idx;

		for (node_idx = TRIE_NODE(trie, current).start;
		     node_idx < node_end && string_bytes[string_idx] != '\0' && string_bytes[string_idx] == TRIE_BYTE(trie, node_idx);
		     node_idx++, string_idx++);

		if (node_idx == node_end) {
			if (string_bytes[string_idx] == '\0') {
				return current; /* Got an exact match */
			} else if (string_idx == strlen(APPLE_WEBCLIP_ID_PREFIX) &&
				   0 == strncmp((const char *)string_bytes, APPLE_WEBCLIP_ID_PREFIX, string_idx)) {
				string_bytes[string_idx] = '\0'; 
				return current; /* Got an apple webclip id prefix match */
			} else if (TRIE_NODE(trie, current).child_map != NULL_TRIE_IDX) {
				next = TRIE_CHILD(trie, current, string_bytes[string_idx]);
			}
		}
		current = next;
	}

	return NULL_TRIE_IDX;
}