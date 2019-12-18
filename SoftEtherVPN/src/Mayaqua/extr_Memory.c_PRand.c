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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Rc4; } ;
typedef  TYPE_1__ PRAND ;

/* Variables and functions */
 int /*<<< orphan*/  Encrypt (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (void*,int /*<<< orphan*/ ) ; 

void PRand(PRAND *p, void *data, UINT size)
{
	if (p == NULL)
	{
		return;
	}

	Zero(data, size);

	Encrypt(p->Rc4, data, data, size);
}