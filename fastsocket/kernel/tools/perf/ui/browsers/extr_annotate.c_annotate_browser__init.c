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

/* Variables and functions */
 int /*<<< orphan*/  annotate__config ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void annotate_browser__init(void)
{
	perf_config(annotate__config, NULL);
}