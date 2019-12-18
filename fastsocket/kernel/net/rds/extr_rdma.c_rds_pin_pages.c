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

/* Variables and functions */
 int EFAULT ; 
 int get_user_pages_fast (unsigned long,unsigned int,int,struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int rds_pin_pages(unsigned long user_addr, unsigned int nr_pages,
			struct page **pages, int write)
{
	int ret;

	ret = get_user_pages_fast(user_addr, nr_pages, write, pages);

	if (ret >= 0 && ret < nr_pages) {
		while (ret--)
			put_page(pages[ret]);
		ret = -EFAULT;
	}

	return ret;
}