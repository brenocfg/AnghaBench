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

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int /*<<< orphan*/ ) ; 
 void* Malloc (int /*<<< orphan*/ ) ; 

void *Clone(void *addr, UINT size)
{
	void *ret;
	// Validate arguments
	if (addr == NULL)
	{
		return NULL;
	}

	ret = Malloc(size);
	Copy(ret, addr, size);

	return ret;
}