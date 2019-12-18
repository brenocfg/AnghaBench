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
struct blk_integrity {int /*<<< orphan*/  flags; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTEGRITY_FLAG_WRITE ; 
 unsigned long simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static ssize_t integrity_write_store(struct blk_integrity *bi,
				     const char *page, size_t count)
{
	char *p = (char *) page;
	unsigned long val = simple_strtoul(p, &p, 10);

	if (val)
		bi->flags |= INTEGRITY_FLAG_WRITE;
	else
		bi->flags &= ~INTEGRITY_FLAG_WRITE;

	return count;
}