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
 int /*<<< orphan*/  SHA1 (void*,scalar_t__,void*) ; 
#define  SHA1_160 131 
 int /*<<< orphan*/  SHA256 (void*,scalar_t__,void*) ; 
#define  SHA2_256 130 
#define  SHA2_384 129 
#define  SHA2_512 128 
 int /*<<< orphan*/  SHA384 (void*,scalar_t__,void*) ; 
 int /*<<< orphan*/  SHA512 (void*,scalar_t__,void*) ; 

void Sha(UINT sha_type, void *dst, void *src, UINT size)
{
	// Validate arguments
	if (dst == NULL || (src == NULL && size != 0))
	{
		return;
	}

	switch(sha_type) {
	case SHA1_160:
		SHA1(src, size, dst);
		break;
	case SHA2_256:
		SHA256(src, size, dst);
		break;
	case SHA2_384:
		SHA384(src, size, dst);
		break;
	case SHA2_512:
		SHA512(src, size, dst);
		break;
	}
}