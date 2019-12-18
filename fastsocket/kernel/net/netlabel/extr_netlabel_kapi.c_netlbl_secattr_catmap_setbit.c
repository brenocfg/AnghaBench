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
typedef  int u32 ;
struct netlbl_lsm_secattr_catmap {int startbit; int* bitmap; struct netlbl_lsm_secattr_catmap* next; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int NETLBL_CATMAP_BIT ; 
 int NETLBL_CATMAP_MAPSIZE ; 
 int NETLBL_CATMAP_SIZE ; 
 struct netlbl_lsm_secattr_catmap* netlbl_secattr_catmap_alloc (int /*<<< orphan*/ ) ; 

int netlbl_secattr_catmap_setbit(struct netlbl_lsm_secattr_catmap *catmap,
				 u32 bit,
				 gfp_t flags)
{
	struct netlbl_lsm_secattr_catmap *iter = catmap;
	u32 node_bit;
	u32 node_idx;

	while (iter->next != NULL &&
	       bit >= (iter->startbit + NETLBL_CATMAP_SIZE))
		iter = iter->next;
	if (bit >= (iter->startbit + NETLBL_CATMAP_SIZE)) {
		iter->next = netlbl_secattr_catmap_alloc(flags);
		if (iter->next == NULL)
			return -ENOMEM;
		iter = iter->next;
		iter->startbit = bit & ~(NETLBL_CATMAP_SIZE - 1);
	}

	/* gcc always rounds to zero when doing integer division */
	node_idx = (bit - iter->startbit) / NETLBL_CATMAP_MAPSIZE;
	node_bit = bit - iter->startbit - (NETLBL_CATMAP_MAPSIZE * node_idx);
	iter->bitmap[node_idx] |= NETLBL_CATMAP_BIT << node_bit;

	return 0;
}