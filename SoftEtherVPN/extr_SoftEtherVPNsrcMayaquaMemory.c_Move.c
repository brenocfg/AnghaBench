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

/* Variables and functions */
 int /*<<< orphan*/  KS_COPY_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,scalar_t__) ; 

void Move(void *dst, void *src, UINT size)
{
	// Validate arguments
	if (dst == NULL || src == NULL || size == 0 || dst == src)
	{
		return;
	}

	// KS
	KS_INC(KS_COPY_COUNT);

	memmove(dst, src, size);
}