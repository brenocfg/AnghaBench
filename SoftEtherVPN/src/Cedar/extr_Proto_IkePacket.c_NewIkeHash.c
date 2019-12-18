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
struct TYPE_8__ {int /*<<< orphan*/  HashesList; } ;
struct TYPE_7__ {char* Name; scalar_t__ HashSize; scalar_t__ HashId; } ;
typedef  TYPE_1__ IKE_HASH ;
typedef  TYPE_2__ IKE_ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

IKE_HASH *NewIkeHash(IKE_ENGINE *e, UINT hash_id, char *name, UINT size)
{
	IKE_HASH *h;
	// Validate arguments
	if (e == NULL || name == NULL || size == 0)
	{
		return NULL;
	}

	h = ZeroMalloc(sizeof(IKE_HASH));

	h->HashId = hash_id;
	h->Name = name;
	h->HashSize = size;

	Add(e->HashesList, h);

	return h;
}