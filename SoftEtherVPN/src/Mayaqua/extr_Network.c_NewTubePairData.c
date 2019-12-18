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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBEPAIR_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 TYPE_1__* ZeroMalloc (int) ; 

TUBEPAIR_DATA *NewTubePairData()
{
	TUBEPAIR_DATA *d = ZeroMalloc(sizeof(TUBEPAIR_DATA));

	d->Ref = NewRef();

	d->Lock = NewLock();

	return d;
}