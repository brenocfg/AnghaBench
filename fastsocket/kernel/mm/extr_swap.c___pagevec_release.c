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
struct pagevec {int /*<<< orphan*/  cold; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 
 int /*<<< orphan*/  release_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __pagevec_release(struct pagevec *pvec)
{
	lru_add_drain();
	release_pages(pvec->pages, pagevec_count(pvec), pvec->cold);
	pagevec_reinit(pvec);
}