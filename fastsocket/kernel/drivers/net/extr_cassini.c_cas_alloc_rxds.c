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
struct cas {int dummy; } ;

/* Variables and functions */
 int N_RX_DESC_RINGS ; 
 scalar_t__ cas_alloc_rx_desc (struct cas*,int) ; 
 int /*<<< orphan*/  cas_free_rxds (struct cas*) ; 

__attribute__((used)) static int cas_alloc_rxds(struct cas *cp)
{
	int i;

	for (i = 0; i < N_RX_DESC_RINGS; i++) {
		if (cas_alloc_rx_desc(cp, i) < 0) {
			cas_free_rxds(cp);
			return -1;
		}
	}
	return 0;
}