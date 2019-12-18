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
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  sh2_drc_finish (int /*<<< orphan*/ *) ; 

void sh2_finish(SH2 *sh2)
{
#ifdef DRC_SH2
	sh2_drc_finish(sh2);
#endif
}