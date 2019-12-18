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
typedef  int /*<<< orphan*/  DECLARE_PCI_UNMAP_ADDR ;

/* Variables and functions */

__attribute__((used)) static inline int need_skb_unmap(void)
{
	/*
	 * This structure is used to tell if the platfrom needs buffer
	 * unmapping by checking if DECLARE_PCI_UNMAP_ADDR defines anything.
	 */
	struct dummy {
		DECLARE_PCI_UNMAP_ADDR(addr);
	};

	return sizeof(struct dummy) != 0;
}