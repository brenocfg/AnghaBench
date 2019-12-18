#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (void*) ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemToBuf (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rand (void*,int /*<<< orphan*/ ) ; 

BUF *RandBuf(UINT size)
{
	void *data = Malloc(size);
	BUF *ret;

	Rand(data, size);

	ret = MemToBuf(data, size);

	Free(data);

	return ret;
}