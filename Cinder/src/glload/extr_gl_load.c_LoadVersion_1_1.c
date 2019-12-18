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
 scalar_t__ LoadCore_Version_1_0 () ; 
 scalar_t__ LoadCore_Version_1_0_Comp () ; 
 scalar_t__ LoadCore_Version_1_1 () ; 
 scalar_t__ LoadCore_Version_1_1_Comp () ; 

__attribute__((used)) static int LoadVersion_1_1()
{
	int numFailed = 0;
	numFailed += LoadCore_Version_1_0();
	numFailed += LoadCore_Version_1_0_Comp();
	numFailed += LoadCore_Version_1_1();
	numFailed += LoadCore_Version_1_1_Comp();
	return numFailed;
}