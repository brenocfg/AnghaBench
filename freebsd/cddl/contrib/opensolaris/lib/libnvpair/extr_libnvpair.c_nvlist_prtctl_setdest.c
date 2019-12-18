#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nvlist_prtctl_t ;
struct TYPE_3__ {int /*<<< orphan*/ * nvprt_fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

void
nvlist_prtctl_setdest(nvlist_prtctl_t pctl, FILE *fp)
{
	pctl->nvprt_fp = fp;
}