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
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (char*,char*,size_t) ; 
 char* page_address (struct page*) ; 

__attribute__((used)) static int page_is_zero(struct page *p, unsigned int offset, size_t len)
{
	char *a = page_address(p) + offset;
	return ((*(u32 *) a) == 0 &&
		memcmp(a, a + 4, len - 4) == 0);
}