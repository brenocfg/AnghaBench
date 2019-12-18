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
 int /*<<< orphan*/  ERI_PERFMON_PGM ; 
 int /*<<< orphan*/  PGM_PMEN ; 
 int /*<<< orphan*/  eri_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xtensa_perfmon_start(void)
{
    eri_write(ERI_PERFMON_PGM, PGM_PMEN);
}