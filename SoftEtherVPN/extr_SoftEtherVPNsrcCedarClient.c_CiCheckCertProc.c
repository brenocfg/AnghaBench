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
typedef  int /*<<< orphan*/  X ;
struct TYPE_5__ {int CheckServerCert; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ServerCert; } ;
struct TYPE_4__ {TYPE_2__* Account; } ;
typedef  TYPE_1__ SESSION ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int CheckXDateNow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ *) ; 
 scalar_t__ CompareX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

bool CiCheckCertProc(SESSION *s, CONNECTION *c, X *server_x, bool *expired)
{
#ifdef	OS_WIN32
	ACCOUNT *a;
	X *old_x = NULL;
	UI_CHECKCERT dlg;
	// Validate arguments
	if (s == NULL || c == NULL || server_x == NULL)
	{
		return false;
	}

	if (expired != NULL)
	{
		*expired = false;
	}

	Zero(&dlg, sizeof(dlg));

	a = s->Account;
	if (a == NULL)
	{
		return false;
	}

	Lock(a->lock);
	{
		if (a->CheckServerCert == false)
		{
			// Not to validate the server certificate
			Unlock(a->lock);
			return true;
		}

		if (a->ServerCert != NULL)
		{
			old_x = CloneX(a->ServerCert);
		}
	}
	Unlock(a->lock);

	if (CheckXDateNow(server_x) == false)
	{
		// Expired
		if (old_x != NULL)
		{
			FreeX(old_x);
		}

		if (expired != NULL)
		{
			*expired = true;
		}

		return false;
	}

	if (old_x != NULL)
	{
		if (CompareX(old_x, server_x))
		{
			// Matched exactly to the certificate that is already registered
			if (old_x != NULL)
			{
				FreeX(old_x);
			}
			return true;
		}
		else
		{
			dlg.DiffWarning = true;
		}
	}

	// Because this certificate can not be trusted, confirm to be trusted by showing a dialog box
	UniStrCpy(dlg.AccountName, sizeof(dlg.AccountName), a->ClientOption->AccountName);
	StrCpy(dlg.ServerName, sizeof(dlg.ServerName), a->ClientOption->Hostname);
	dlg.x = server_x;
	dlg.old_x = old_x;
	
	dlg.Session = s;
	AddRef(s->ref);

	CncCheckCert(s, &dlg);

	ReleaseSession(s);

	if (old_x != NULL)
	{
		FreeX(old_x);
	}

	if (dlg.Ok && dlg.SaveServerCert)
	{
		// Save the server certificate and trust it from the next time
		Lock(a->lock);
		{
			if (a->ServerCert != NULL)
			{
				FreeX(a->ServerCert);
			}

			a->ServerCert = CloneX(server_x);
		}
		Unlock(a->lock);
		CiSaveConfigurationFile(s->Cedar->Client);
	}

	return dlg.Ok;
#else	// OS_WIN32
	ACCOUNT *a;
	X *old_x = NULL;
	// Validate arguments
	if (s == NULL || c == NULL || server_x == NULL)
	{
		return false;
	}

	if (expired != NULL)
	{
		*expired = false;
	}

	a = s->Account;
	if (a == NULL)
	{
		return false;
	}

	Lock(a->lock);
	{
		if (a->CheckServerCert == false)
		{
			// Not to validate the server certificate
			Unlock(a->lock);
			return true;
		}

		if (a->ServerCert != NULL)
		{
			old_x = CloneX(a->ServerCert);
		}
	}
	Unlock(a->lock);

	if (CheckXDateNow(server_x) == false)
	{
		// Expired
		if (old_x != NULL)
		{
			FreeX(old_x);
		}

		if (expired != NULL)
		{
			*expired = true;
		}

		return false;
	}

	if (old_x != NULL)
	{
		if (CompareX(old_x, server_x))
		{
			// Exactly matched to the certificate that is already registered
			if (old_x != NULL)
			{
				FreeX(old_x);
			}
			return true;
		}
		else
		{
			// Mismatch
			if (old_x != NULL)
			{
				FreeX(old_x);
			}
			return false;
		}
	}

	return false;
#endif	// OS_WIN32
}