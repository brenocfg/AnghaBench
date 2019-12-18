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
struct cas {int /*<<< orphan*/ *** rx_pages; } ;
typedef  int /*<<< orphan*/  cas_page_t ;

/* Variables and functions */
 int RX_DESC_RINGN_SIZE (int) ; 
 int /*<<< orphan*/  cas_page_free (struct cas*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cas_free_rx_desc(struct cas *cp, int ring)
{
	cas_page_t **page = cp->rx_pages[ring];
	int i, size;

	size = RX_DESC_RINGN_SIZE(ring);
	for (i = 0; i < size; i++) {
		if (page[i]) {
			cas_page_free(cp, page[i]);
			page[i] = NULL;
		}
	}
}