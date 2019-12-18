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
typedef  size_t UINT ;

/* Variables and functions */
 size_t B64_Encode (char*,void*,size_t) ; 
 int /*<<< orphan*/  Base64ToSafe64 (char*) ; 

void EncodeSafe64(char *dst, void *src, UINT src_size)
{
	UINT size;
	if (dst == NULL || src == NULL)
	{
		return;
	}

	size = B64_Encode(dst, src, src_size);
	dst[size] = 0;

	Base64ToSafe64(dst);
}