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
 unsigned int PAGE_SIZE ; 
 struct page* nth_page (struct page*,unsigned long) ; 

__attribute__((used)) static inline void __segment_seek(struct page **page, unsigned int *poff,
				  unsigned int *plen, unsigned int off)
{
	unsigned long n;

	*poff += off;
	n = *poff / PAGE_SIZE;
	if (n)
		*page = nth_page(*page, n);

	*poff = *poff % PAGE_SIZE;
	*plen -= off;
}