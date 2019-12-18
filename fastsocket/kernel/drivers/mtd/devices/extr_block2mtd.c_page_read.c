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
struct address_space {int dummy; } ;

/* Variables and functions */
 struct page* read_mapping_page (struct address_space*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *page_read(struct address_space *mapping, int index)
{
	return read_mapping_page(mapping, index, NULL);
}