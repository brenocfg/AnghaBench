#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ AuthType; int /*<<< orphan*/  lock; void* AuthData; } ;
typedef  TYPE_1__ USER ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  NtLmSecureHash; int /*<<< orphan*/  HashedKey; } ;
typedef  TYPE_2__ AUTHPASSWORD ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_ANONYMOUS ; 
 scalar_t__ AUTHTYPE_PASSWORD ; 
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeAuthData (scalar_t__,void*) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SetUserAuthData(USER *u, UINT authtype, void *authdata)
{
	// Validate arguments
	if (u == NULL)
	{
		return;
	}
	if (authtype != AUTHTYPE_ANONYMOUS && authdata == NULL)
	{
		return;
	}

	Lock(u->lock);
	{
		if (u->AuthType != AUTHTYPE_ANONYMOUS)
		{
			if (u->AuthType == AUTHTYPE_PASSWORD && authtype == AUTHTYPE_PASSWORD)
			{
				AUTHPASSWORD *pw_old = (AUTHPASSWORD *)u->AuthData;
				AUTHPASSWORD *pw_new = (AUTHPASSWORD *)authdata;

				// Copy NTLM hash for new password from old data, if the password is not changed 
				// and management tool don't send NTLM hash.

				if (Cmp(pw_old->HashedKey, pw_new->HashedKey, SHA1_SIZE) == 0)
				{
					if (IsZero(pw_new->NtLmSecureHash, MD5_SIZE))
					{
						Copy(pw_new->NtLmSecureHash, pw_old->NtLmSecureHash, MD5_SIZE);
					}
				}
			}

			// Free current authentication data
			FreeAuthData(u->AuthType, u->AuthData);
		}
		// Set new authentication data
		u->AuthType = authtype;
		u->AuthData = authdata;
	}
	Unlock(u->lock);
}