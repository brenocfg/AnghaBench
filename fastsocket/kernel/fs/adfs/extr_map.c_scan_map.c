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
struct adfs_sb_info {unsigned int s_idlen; unsigned int s_map_size; struct adfs_discmap* s_map; } ;
struct adfs_discmap {scalar_t__ dm_startblk; scalar_t__ dm_startbit; } ;

/* Variables and functions */
 int lookup_zone (struct adfs_discmap*,unsigned int const,unsigned int const,unsigned int*) ; 

__attribute__((used)) static int
scan_map(struct adfs_sb_info *asb, unsigned int zone,
	 const unsigned int frag_id, unsigned int mapoff)
{
	const unsigned int idlen = asb->s_idlen;
	struct adfs_discmap *dm, *dm_end;
	int result;

	dm	= asb->s_map + zone;
	zone	= asb->s_map_size;
	dm_end	= asb->s_map + zone;

	do {
		result = lookup_zone(dm, idlen, frag_id, &mapoff);

		if (result != -1)
			goto found;

		dm ++;
		if (dm == dm_end)
			dm = asb->s_map;
	} while (--zone > 0);

	return -1;
found:
	result -= dm->dm_startbit;
	result += dm->dm_startblk;

	return result;
}