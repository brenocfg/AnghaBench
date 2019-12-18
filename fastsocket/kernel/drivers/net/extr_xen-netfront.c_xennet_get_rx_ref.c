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
struct netfront_info {int /*<<< orphan*/ * grant_rx_ref; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int xennet_rxidx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grant_ref_t xennet_get_rx_ref(struct netfront_info *np,
					    RING_IDX ri)
{
	int i = xennet_rxidx(ri);
	grant_ref_t ref = np->grant_rx_ref[i];
	np->grant_rx_ref[i] = GRANT_INVALID_REF;
	return ref;
}