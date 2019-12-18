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
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __balloon_append (struct page*) ; 
 int /*<<< orphan*/  dec_totalhigh_pages () ; 
 int /*<<< orphan*/  totalram_pages ; 

__attribute__((used)) static void balloon_append(struct page *page)
{
	__balloon_append(page);
	if (PageHighMem(page))
		dec_totalhigh_pages();
	totalram_pages--;
}