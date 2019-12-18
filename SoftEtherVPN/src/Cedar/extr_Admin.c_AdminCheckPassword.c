#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {TYPE_1__* Server; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_10__ {scalar_t__ ServerType; int /*<<< orphan*/  HashedPassword; } ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  ERR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERR_FARM_MEMBER_HUB_ADMIN ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 TYPE_2__* GetHub (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SecurePassword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ SiIsEmptyPassword (int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_3__*) ; 

UINT AdminCheckPassword(CEDAR *c, void *random, void *secure_password, char *hubname,
						bool accept_empty_password, bool *is_password_empty)
{
	UCHAR check[SHA1_SIZE];
	bool b_dummy;
	// Validate arguments
	if (c == NULL || random == NULL || secure_password == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}
	if (is_password_empty == NULL)
	{
		is_password_empty = &b_dummy;
	}

	*is_password_empty = false;

	if (hubname == NULL || StrLen(hubname) == 0)
	{
		// Server admin mode
		Lock(c->lock);
		{
			if (accept_empty_password && SiIsEmptyPassword(c->Server->HashedPassword))
			{
				// blank password
				*is_password_empty = true;
			}

			SecurePassword(check, c->Server->HashedPassword, random);
		}
		Unlock(c->lock);

		if (Cmp(check, secure_password, SHA1_SIZE) != 0)
		{
			// Password incorrect
			return ERR_ACCESS_DENIED;
		}
	}
	else
	{
		HUB *h;

#if	0
		if (c->Server->ServerType == SERVER_TYPE_FARM_MEMBER)
		{
			// In cluster member mode, hub admin mode is disabled
			return ERR_FARM_MEMBER_HUB_ADMIN;
		}
#endif

		// Hub admin mode
		LockHubList(c);
		{
			h = GetHub(c, hubname);
		}
		UnlockHubList(c);

		if (h == NULL)
		{
			// Specified hub is not found
			return ERR_HUB_NOT_FOUND;
		}

		Lock(h->lock);
		{
			if (accept_empty_password && SiIsEmptyPassword(h->HashedPassword))
			{
				// User specified blank password
				*is_password_empty = true;
			}

			SecurePassword(check, h->HashedPassword, random);
		}
		Unlock(h->lock);

		ReleaseHub(h);

		if (Cmp(check, secure_password, SHA1_SIZE) != 0)
		{
			// Incorrect password
			return ERR_ACCESS_DENIED;
		}
	}

	return ERR_NO_ERROR;
}