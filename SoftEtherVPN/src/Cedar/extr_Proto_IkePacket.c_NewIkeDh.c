#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {char* Name; scalar_t__ KeySize; scalar_t__ DhId; } ;
struct TYPE_7__ {int /*<<< orphan*/  DhsList; } ;
typedef  TYPE_1__ IKE_ENGINE ;
typedef  TYPE_2__ IKE_DH ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IKE_DH *NewIkeDh(IKE_ENGINE *e, UINT dh_id, char *name, UINT key_size)
{
	IKE_DH *d;
	// Validate arguments
	if (e == NULL || name == NULL || key_size == 0)
	{
		return NULL;
	}

	d = ZeroMalloc(sizeof(IKE_DH));

	d->DhId = dh_id;
	d->Name = name;
	d->KeySize = key_size;

	Add(e->DhsList, d);

	return d;
}