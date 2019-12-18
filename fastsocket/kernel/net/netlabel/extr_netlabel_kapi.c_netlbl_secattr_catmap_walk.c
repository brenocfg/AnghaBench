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
typedef  scalar_t__ u32 ;
struct netlbl_lsm_secattr_catmap {scalar_t__ startbit; scalar_t__* bitmap; struct netlbl_lsm_secattr_catmap* next; } ;
typedef  int NETLBL_CATMAP_MAPTYPE ;

/* Variables and functions */
 int ENOENT ; 
 int NETLBL_CATMAP_BIT ; 
 scalar_t__ NETLBL_CATMAP_MAPCNT ; 
 scalar_t__ NETLBL_CATMAP_MAPSIZE ; 
 scalar_t__ NETLBL_CATMAP_SIZE ; 

int netlbl_secattr_catmap_walk(struct netlbl_lsm_secattr_catmap *catmap,
			       u32 offset)
{
	struct netlbl_lsm_secattr_catmap *iter = catmap;
	u32 node_idx;
	u32 node_bit;
	NETLBL_CATMAP_MAPTYPE bitmap;

	if (offset > iter->startbit) {
		while (offset >= (iter->startbit + NETLBL_CATMAP_SIZE)) {
			iter = iter->next;
			if (iter == NULL)
				return -ENOENT;
		}
		node_idx = (offset - iter->startbit) / NETLBL_CATMAP_MAPSIZE;
		node_bit = offset - iter->startbit -
			   (NETLBL_CATMAP_MAPSIZE * node_idx);
	} else {
		node_idx = 0;
		node_bit = 0;
	}
	bitmap = iter->bitmap[node_idx] >> node_bit;

	for (;;) {
		if (bitmap != 0) {
			while ((bitmap & NETLBL_CATMAP_BIT) == 0) {
				bitmap >>= 1;
				node_bit++;
			}
			return iter->startbit +
				(NETLBL_CATMAP_MAPSIZE * node_idx) + node_bit;
		}
		if (++node_idx >= NETLBL_CATMAP_MAPCNT) {
			if (iter->next != NULL) {
				iter = iter->next;
				node_idx = 0;
			} else
				return -ENOENT;
		}
		bitmap = iter->bitmap[node_idx];
		node_bit = 0;
	}

	return -ENOENT;
}