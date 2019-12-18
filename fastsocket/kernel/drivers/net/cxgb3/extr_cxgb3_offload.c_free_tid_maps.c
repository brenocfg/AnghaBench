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
struct tid_info {int /*<<< orphan*/  tid_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb_free_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_tid_maps(struct tid_info *t)
{
	cxgb_free_mem(t->tid_tab);
}