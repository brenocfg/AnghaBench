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
struct ttm_tt {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_calloc_large (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ttm_tt_alloc_page_directory(struct ttm_tt *ttm)
{
	ttm->pages = drm_calloc_large(ttm->num_pages, sizeof(void*));
}