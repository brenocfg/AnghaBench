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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {void (* update ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 TYPE_1__* progress_fns ; 
 void stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void ui_progress__update(u64 curr, u64 total, const char *title)
{
	return progress_fns->update(curr, total, title);
}