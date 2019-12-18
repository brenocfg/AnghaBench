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
struct dm_kcopyd_client {scalar_t__ nr_free_pages; scalar_t__ nr_reserved_pages; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  drop_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void client_free_pages(struct dm_kcopyd_client *kc)
{
	BUG_ON(kc->nr_free_pages != kc->nr_reserved_pages);
	drop_pages(kc->pages);
	kc->pages = NULL;
	kc->nr_free_pages = kc->nr_reserved_pages = 0;
}