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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {char* RadiusServerName; char* RadiusSuffixFilter; int /*<<< orphan*/  RadiusOptionLock; TYPE_1__* RadiusSecret; scalar_t__ RadiusRetryInterval; scalar_t__ RadiusServerPort; } ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 char* ZeroMalloc (scalar_t__) ; 

bool GetRadiusServerEx2(HUB *hub, char *name, UINT size, UINT *port, char *secret, UINT secret_size, UINT *interval, char *suffix_filter, UINT suffix_filter_size)
{
	bool ret = false;
	// Validate arguments
	if (hub == NULL || name == NULL || port == NULL || secret == NULL || interval == NULL)
	{
		return false;
	}

	Lock(hub->RadiusOptionLock);
	{
		if (hub->RadiusServerName != NULL)
		{
			char *tmp;
			UINT tmp_size;
			StrCpy(name, size, hub->RadiusServerName);
			*port = hub->RadiusServerPort;
			*interval = hub->RadiusRetryInterval;

			tmp_size = hub->RadiusSecret->Size + 1;
			tmp = ZeroMalloc(tmp_size);
			Copy(tmp, hub->RadiusSecret->Buf, hub->RadiusSecret->Size);
			StrCpy(secret, secret_size, tmp);
			Free(tmp);

			if (suffix_filter != NULL)
			{
				StrCpy(suffix_filter, suffix_filter_size, hub->RadiusSuffixFilter);
			}

			ret = true;
		}
	}
	Unlock(hub->RadiusOptionLock);

	return ret;
}