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
struct TYPE_3__ {int /*<<< orphan*/  Ctx; scalar_t__ IsHMac; scalar_t__ IsNullMd; } ;
typedef  TYPE_1__ MD ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int EVP_DigestFinal_ex (int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 int EVP_DigestUpdate (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int HMAC_Final (int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 int HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HMAC_Update (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  OpenSSL_Error () ; 

UINT MdProcess(MD *md, void *dest, void *src, UINT size)
{
	UINT len = 0;

	// Validate arguments
	if (md == NULL || md->IsNullMd || dest == NULL || (src == NULL && size != 0))
	{
		return 0;
	}

	if (md->IsHMac)
	{
		// WARNING: Do not remove the call to HMAC_Init_ex(), it's required even if the context is initialized by SetMdKey()!
		if (HMAC_Init_ex(md->Ctx, NULL, 0, NULL, NULL) == false)
		{
			Debug("MdProcess(): HMAC_Init_ex() failed with error: %s\n", OpenSSL_Error());
			return 0;
		}

		if (HMAC_Update(md->Ctx, src, size) == false)
		{
			Debug("MdProcess(): HMAC_Update() failed with error: %s\n", OpenSSL_Error());
			return 0;
		}

		if (HMAC_Final(md->Ctx, dest, &len) == false)
		{
			Debug("MdProcess(): HMAC_Final() failed with error: %s\n", OpenSSL_Error());
		}
	}
	else
	{
		if (EVP_DigestUpdate(md->Ctx, src, size) == false)
		{
			Debug("MdProcess(): EVP_DigestUpdate() failed with error: %s\n", OpenSSL_Error());
			return 0;
		}

		if (EVP_DigestFinal_ex(md->Ctx, dest, &len) == false)
		{
			Debug("MdProcess(): EVP_DigestFinal_ex() failed with error: %s\n", OpenSSL_Error());
		}
	}

	return len;
}