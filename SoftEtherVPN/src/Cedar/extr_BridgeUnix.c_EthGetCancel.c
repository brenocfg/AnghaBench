#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
struct TYPE_5__ {TYPE_2__* Cancel; } ;
typedef  TYPE_1__ ETH ;
typedef  TYPE_2__ CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 

CANCEL *EthGetCancel(ETH *e)
{
	CANCEL *c;
	// Validate arguments
	if (e == NULL)
	{
		return NULL;
	}

	c = e->Cancel;
	AddRef(c->ref);

	return c;
}