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
typedef  int /*<<< orphan*/  YuiScsp ;

/* Variables and functions */
 int /*<<< orphan*/  yui_scsp_fill (int /*<<< orphan*/ *) ; 

void yui_scsp_update(YuiScsp * scsp) {
	yui_scsp_fill(scsp);
}