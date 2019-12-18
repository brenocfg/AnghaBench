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
 int /*<<< orphan*/  free_hot_cold_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mm_page_free_direct (struct page*,int /*<<< orphan*/ ) ; 

void free_hot_page(struct page *page)
{
	trace_mm_page_free_direct(page, 0);
	free_hot_cold_page(page, 0);
}