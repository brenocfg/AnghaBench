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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KMMIO_PAGE_HASH_BITS ; 
 size_t hash_long (unsigned long,int /*<<< orphan*/ ) ; 
 struct list_head* kmmio_page_table ; 

__attribute__((used)) static struct list_head *kmmio_page_list(unsigned long page)
{
	return &kmmio_page_table[hash_long(page, KMMIO_PAGE_HASH_BITS)];
}