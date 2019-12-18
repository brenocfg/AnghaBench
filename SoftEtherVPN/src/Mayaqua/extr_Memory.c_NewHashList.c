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
typedef  int UINT ;
struct TYPE_3__ {int Bits; int Size; int /*<<< orphan*/  AllList; int /*<<< orphan*/ * CompareProc; int /*<<< orphan*/ * GetHashProc; void* Entries; int /*<<< orphan*/  Ref; int /*<<< orphan*/  Lock; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ HASH_LIST ;
typedef  int /*<<< orphan*/  GET_HASH ;
typedef  int /*<<< orphan*/  COMPARE ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int Power (int,int) ; 
 void* ZeroMalloc (int) ; 

HASH_LIST *NewHashList(GET_HASH *get_hash_proc, COMPARE *compare_proc, UINT bits, bool make_list)
{
	HASH_LIST *h;
	// Validate arguments
	if (get_hash_proc == NULL || compare_proc == NULL)
	{
		return NULL;
	}
	if (bits == 0)
	{
		bits = 16;
	}

	bits = MIN(bits, 31);

	h = ZeroMalloc(sizeof(HASH_LIST));

	h->Bits = bits;
	h->Size = Power(2, bits);

	h->Lock = NewLock();
	h->Ref = NewRef();

	h->Entries = ZeroMalloc(sizeof(LIST *) * h->Size);

	h->GetHashProc = get_hash_proc;
	h->CompareProc = compare_proc;

	if (make_list)
	{
		h->AllList = NewListFast(NULL);
	}

	return h;
}