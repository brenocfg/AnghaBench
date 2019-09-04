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
typedef  int uint32_t ;
typedef  int nspace_type_t ;

/* Variables and functions */
#define  NSPACE_HANDLER_NSPACE 129 
#define  NSPACE_HANDLER_SNAPSHOT 128 
 int NSPACE_ITEM_ALL_EVENT_TYPES ; 
 int NSPACE_ITEM_NSPACE_EVENT ; 
 int NSPACE_ITEM_SNAPSHOT_EVENT ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static inline int nspace_flags_matches_handler(uint32_t event_flags, nspace_type_t nspace_type)
{
	switch(nspace_type) {
		case NSPACE_HANDLER_NSPACE:
			return (event_flags & NSPACE_ITEM_ALL_EVENT_TYPES) == NSPACE_ITEM_NSPACE_EVENT;
		case NSPACE_HANDLER_SNAPSHOT:
			return (event_flags & NSPACE_ITEM_ALL_EVENT_TYPES) == NSPACE_ITEM_SNAPSHOT_EVENT;
		default:
			printf("nspace_flags_matches_handler: invalid type %u\n", (int)nspace_type);
			return 0;
	}
}