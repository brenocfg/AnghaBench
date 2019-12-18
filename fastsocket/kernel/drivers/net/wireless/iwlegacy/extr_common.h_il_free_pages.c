#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_page_order; } ;
struct il_priv {int /*<<< orphan*/  alloc_rxb_page; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
il_free_pages(struct il_priv *il, unsigned long page)
{
	free_pages(page, il->hw_params.rx_page_order);
	il->alloc_rxb_page--;
}