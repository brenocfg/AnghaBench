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
struct page {int dummy; } ;
struct kvec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int copy_pages_to_kvecs(struct kvec *vec, struct page **pages, int len)
{
	int i = 0;
	int t = 0;

	while (t < len) {
		vec[i].iov_base = page_address(pages[i]);
		vec[i].iov_len = PAGE_SIZE;
		i++;
		t += PAGE_SIZE;
	}
	return i;
}