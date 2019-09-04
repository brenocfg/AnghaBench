#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  SockList; } ;
typedef  TYPE_1__ SOCKLIST ;

/* Variables and functions */
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMallocFast (int) ; 

SOCKLIST *NewSockList()
{
	SOCKLIST *sl = ZeroMallocFast(sizeof(SOCKLIST));

	sl->SockList = NewList(NULL);

	return sl;
}