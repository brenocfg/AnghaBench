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
struct netlbl_lsm_secattr_catmap {scalar_t__ startbit; struct netlbl_lsm_secattr_catmap* next; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NETLBL_CATMAP_SIZE ; 
 int netlbl_secattr_catmap_setbit (struct netlbl_lsm_secattr_catmap*,scalar_t__,int /*<<< orphan*/ ) ; 

int netlbl_secattr_catmap_setrng(struct netlbl_lsm_secattr_catmap *catmap,
				 u32 start,
				 u32 end,
				 gfp_t flags)
{
	int ret_val = 0;
	struct netlbl_lsm_secattr_catmap *iter = catmap;
	u32 iter_max_spot;
	u32 spot;

	/* XXX - This could probably be made a bit faster by combining writes
	 * to the catmap instead of setting a single bit each time, but for
	 * right now skipping to the start of the range in the catmap should
	 * be a nice improvement over calling the individual setbit function
	 * repeatedly from a loop. */

	while (iter->next != NULL &&
	       start >= (iter->startbit + NETLBL_CATMAP_SIZE))
		iter = iter->next;
	iter_max_spot = iter->startbit + NETLBL_CATMAP_SIZE;

	for (spot = start; spot <= end && ret_val == 0; spot++) {
		if (spot >= iter_max_spot && iter->next != NULL) {
			iter = iter->next;
			iter_max_spot = iter->startbit + NETLBL_CATMAP_SIZE;
		}
		ret_val = netlbl_secattr_catmap_setbit(iter, spot, GFP_ATOMIC);
	}

	return ret_val;
}