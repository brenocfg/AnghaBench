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
struct pt1 {int /*<<< orphan*/ * adaps; } ;

/* Variables and functions */
 int PT1_NR_ADAPS ; 
 int /*<<< orphan*/  pt1_free_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt1_cleanup_adapters(struct pt1 *pt1)
{
	int i;
	for (i = 0; i < PT1_NR_ADAPS; i++)
		pt1_free_adapter(pt1->adaps[i]);
}