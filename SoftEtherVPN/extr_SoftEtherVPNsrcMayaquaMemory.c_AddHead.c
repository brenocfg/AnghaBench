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
typedef  scalar_t__ UINT ;
typedef  void UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 void* Malloc (scalar_t__) ; 

void *AddHead(void *src, UINT src_size, void *head, UINT head_size)
{
	void *ret;
	UINT ret_size;
	// Validate arguments
	if ((src == NULL && src_size != 0) || (head == NULL && head_size != 0))
	{
		return NULL;
	}

	ret_size = src_size + head_size;

	ret = Malloc(ret_size);

	Copy(ret, head, head_size);

	Copy(((UCHAR *)ret) + head_size, src, src_size);

	return ret;
}