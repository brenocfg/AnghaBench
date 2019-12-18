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
struct uwb_dev_addr {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_dev_addr_cmp (struct uwb_dev_addr const*,struct uwb_dev_addr const*) ; 

__attribute__((used)) static inline int uwb_dev_addr_bcast(const struct uwb_dev_addr *addr)
{
	static const struct uwb_dev_addr bcast = { .data = { 0xff, 0xff } };
	return !uwb_dev_addr_cmp(addr, &bcast);
}