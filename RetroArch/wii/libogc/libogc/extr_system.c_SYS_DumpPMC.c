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
 int /*<<< orphan*/  mfpmc1 () ; 
 int /*<<< orphan*/  mfpmc2 () ; 
 int /*<<< orphan*/  mfpmc3 () ; 
 int /*<<< orphan*/  mfpmc4 () ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SYS_DumpPMC()
{
	printf("<%lu load/stores / %lu miss cycles / %lu cycles / %lu instructions>\n",mfpmc1(),mfpmc2(),mfpmc3(),mfpmc4());
}