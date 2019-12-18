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
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int remembered; } ;

/* Variables and functions */
 int /*<<< orphan*/  backgndpid ; 
 TYPE_1__* bgjob ; 
 int /*<<< orphan*/  forcelocal ; 

pid_t
backgndpidval(void)
{
	if (bgjob != NULL && !forcelocal)
		bgjob->remembered = 1;
	return backgndpid;
}