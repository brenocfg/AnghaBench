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
typedef  int /*<<< orphan*/  dummy ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  Rc4; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ PRAND ;

/* Variables and functions */
 int /*<<< orphan*/  Encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NewCrypt (void*,int) ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

PRAND *NewPRand(void *key, UINT key_size)
{
	PRAND *r;
	UCHAR dummy[256];
	if (key == NULL || key_size == 0)
	{
		key = "DUMMY";
		key_size = 5;
	}

	r = ZeroMalloc(sizeof(PRAND));

	Sha1(r->Key, key, key_size);

	r->Rc4 = NewCrypt(key, key_size);

	Zero(dummy, sizeof(dummy));

	Encrypt(r->Rc4, dummy, dummy, 256);

	return r;
}