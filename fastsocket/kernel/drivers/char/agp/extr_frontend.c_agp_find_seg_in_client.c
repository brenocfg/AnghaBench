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
struct agp_segment_priv {unsigned long pg_start; size_t pg_count; int /*<<< orphan*/  prot; } ;
struct agp_client {int num_segments; struct agp_segment_priv** segments; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  unsigned long off_t ;

/* Variables and functions */
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct
agp_segment_priv *agp_find_seg_in_client(const struct agp_client *client,
						unsigned long offset,
					    int size, pgprot_t page_prot)
{
	struct agp_segment_priv *seg;
	int num_segments, i;
	off_t pg_start;
	size_t pg_count;

	pg_start = offset / 4096;
	pg_count = size / 4096;
	seg = *(client->segments);
	num_segments = client->num_segments;

	for (i = 0; i < client->num_segments; i++) {
		if ((seg[i].pg_start == pg_start) &&
		    (seg[i].pg_count == pg_count) &&
		    (pgprot_val(seg[i].prot) == pgprot_val(page_prot))) {
			return seg + i;
		}
	}

	return NULL;
}