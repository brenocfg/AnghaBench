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
 void* dlg_reallocate_gauge (int /*<<< orphan*/ *,char const*,char const*,int,int,int) ; 

void *
dlg_allocate_gauge(const char *title,
		   const char *cprompt,
		   int height,
		   int width,
		   int percent)
{
    return dlg_reallocate_gauge(NULL, title, cprompt, height, width, percent);
}