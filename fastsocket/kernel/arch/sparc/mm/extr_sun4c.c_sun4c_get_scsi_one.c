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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  sun4c_flush_page (unsigned long) ; 
 int /*<<< orphan*/  sun4c_lockarea (char*,unsigned long) ; 
 int /*<<< orphan*/  virt_addr_valid (unsigned long) ; 

__attribute__((used)) static __u32 sun4c_get_scsi_one(struct device *dev, char *bufptr, unsigned long len)
{
	unsigned long page;

	page = ((unsigned long)bufptr) & PAGE_MASK;
	if (!virt_addr_valid(page)) {
		sun4c_flush_page(page);
		return (__u32)bufptr; /* already locked */
	}
	return (__u32)sun4c_lockarea(bufptr, len);
}