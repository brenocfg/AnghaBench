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
struct pagevec {int /*<<< orphan*/  cold; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_hot_cold_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  trace_mm_pagevec_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __pagevec_free(struct pagevec *pvec)
{
	int i = pagevec_count(pvec);

	while (--i >= 0) {
		trace_mm_pagevec_free(pvec->pages[i], pvec->cold);
		free_hot_cold_page(pvec->pages[i], pvec->cold);
	}
}