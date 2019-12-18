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
struct sctp_tsnmap {int len; scalar_t__ num_dup_tsns; void* cumulative_tsn_ack_point; void* max_tsn_seen; void* base_tsn; int /*<<< orphan*/ * tsn_map; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

struct sctp_tsnmap *sctp_tsnmap_init(struct sctp_tsnmap *map, __u16 len,
				     __u32 initial_tsn, gfp_t gfp)
{
	if (!map->tsn_map) {
		map->tsn_map = kzalloc(len>>3, gfp);
		if (map->tsn_map == NULL)
			return NULL;

		map->len = len;
	} else {
		bitmap_zero(map->tsn_map, map->len);
	}

	/* Keep track of TSNs represented by tsn_map.  */
	map->base_tsn = initial_tsn;
	map->cumulative_tsn_ack_point = initial_tsn - 1;
	map->max_tsn_seen = map->cumulative_tsn_ack_point;
	map->num_dup_tsns = 0;

	return map;
}