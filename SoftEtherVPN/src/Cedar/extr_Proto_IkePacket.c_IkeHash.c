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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int HashId; } ;
typedef  TYPE_1__ IKE_HASH ;

/* Variables and functions */
#define  IKE_HASH_MD5_ID 132 
#define  IKE_HASH_SHA1_ID 131 
#define  IKE_HASH_SHA2_256_ID 130 
#define  IKE_HASH_SHA2_384_ID 129 
#define  IKE_HASH_SHA2_512_ID 128 
 int /*<<< orphan*/  Md5 (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Sha1 (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Sha2_256 (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Sha2_384 (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Sha2_512 (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (void*,scalar_t__) ; 

void IkeHash(IKE_HASH *h, void *dst, void *src, UINT size)
{
	// Validate arguments
	if (h == NULL || dst == NULL || (size != 0 && src == NULL))
	{
		Zero(dst, size);
		return;
	}

	switch (h->HashId)
	{
	case IKE_HASH_MD5_ID:
		// MD5
		Md5(dst, src, size);
		break;

	case IKE_HASH_SHA1_ID:
		// SHA-1
		Sha1(dst, src, size);
		break;
	case IKE_HASH_SHA2_256_ID:
		Sha2_256(dst, src, size);
		break;
	case IKE_HASH_SHA2_384_ID:
		Sha2_384(dst, src, size);
		break;
	case IKE_HASH_SHA2_512_ID:
		Sha2_512(dst, src, size);
		break;

	default:
		// Unknown
		Zero(dst, size);
		break;
	}
}