#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int IndexInTubePair; TYPE_1__* Event; TYPE_2__* TubePairData; } ;
struct TYPE_9__ {TYPE_1__* Event2; TYPE_1__* Event1; int /*<<< orphan*/  Ref; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ TUBEPAIR_DATA ;
typedef  TYPE_3__ TUBE ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewTube (int /*<<< orphan*/ ) ; 
 TYPE_2__* NewTubePairData () ; 

void NewTubePair(TUBE **t1, TUBE **t2, UINT size_of_header)
{
	TUBEPAIR_DATA *d;
	// Validate arguments
	if (t1 == NULL || t2 == NULL)
	{
		return;
	}

	*t1 = NewTube(size_of_header);
	*t2 = NewTube(size_of_header);

	(*t1)->IndexInTubePair = 0;
	(*t2)->IndexInTubePair = 1;

	d = NewTubePairData();
	AddRef(d->Ref);

	(*t1)->TubePairData = d;
	(*t2)->TubePairData = d;

	d->Event1 = (*t1)->Event;
	d->Event2 = (*t2)->Event;

	AddRef(d->Event1->ref);
	AddRef(d->Event2->ref);
}