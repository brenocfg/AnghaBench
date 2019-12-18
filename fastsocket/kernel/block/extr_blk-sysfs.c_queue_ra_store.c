#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long ra_pages; } ;
struct request_queue {TYPE_1__ backing_dev_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  queue_var_store (unsigned long*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
queue_ra_store(struct request_queue *q, const char *page, size_t count)
{
	unsigned long ra_kb;
	ssize_t ret = queue_var_store(&ra_kb, page, count);

	q->backing_dev_info.ra_pages = ra_kb >> (PAGE_CACHE_SHIFT - 10);

	return ret;
}