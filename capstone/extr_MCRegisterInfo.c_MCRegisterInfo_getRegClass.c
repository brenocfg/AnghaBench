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
struct TYPE_3__ {unsigned int NumClasses; int /*<<< orphan*/  const* Classes; } ;
typedef  TYPE_1__ MCRegisterInfo ;
typedef  int /*<<< orphan*/  MCRegisterClass ;

/* Variables and functions */

const MCRegisterClass* MCRegisterInfo_getRegClass(const MCRegisterInfo *RI, unsigned i)
{
	//assert(i < getNumRegClasses() && "Register Class ID out of range");
	if (i >= RI->NumClasses)
		return 0;
	return &(RI->Classes[i]);
}