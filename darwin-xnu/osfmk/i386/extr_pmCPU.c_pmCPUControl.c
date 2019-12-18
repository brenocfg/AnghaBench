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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int (* pmCPUControl ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 TYPE_1__* pmDispatch ; 
 int stub1 (int /*<<< orphan*/ ,void*) ; 

int
pmCPUControl(uint32_t cmd, void *datap)
{
    int		rc	= -1;

    if (pmDispatch != NULL
	&& pmDispatch->pmCPUControl != NULL)
	rc = (*pmDispatch->pmCPUControl)(cmd, datap);

    return(rc);
}