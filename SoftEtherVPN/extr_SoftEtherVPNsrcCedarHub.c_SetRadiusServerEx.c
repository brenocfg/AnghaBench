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
struct TYPE_3__ {int /*<<< orphan*/  RadiusOptionLock; void* RadiusSecret; void* RadiusRetryInterval; scalar_t__ RadiusServerPort; int /*<<< orphan*/ * RadiusServerName; } ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStr (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (void*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 void* NewBuf () ; 
 void* RADIUS_RETRY_INTERVAL ; 
 scalar_t__ RADIUS_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  SeekBuf (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (void*,char*,int /*<<< orphan*/ ) ; 

void SetRadiusServerEx(HUB *hub, char *name, UINT port, char *secret, UINT interval)
{
	// Validate arguments
	if (hub == NULL)
	{
		return;
	}

	Lock(hub->RadiusOptionLock);
	{
		if (hub->RadiusServerName != NULL)
		{
			Free(hub->RadiusServerName);
		}

		if (name == NULL)
		{
			hub->RadiusServerName = NULL;
			hub->RadiusServerPort = 0;
			hub->RadiusRetryInterval = RADIUS_RETRY_INTERVAL;
			FreeBuf(hub->RadiusSecret);
		}
		else
		{
			hub->RadiusServerName = CopyStr(name);
			hub->RadiusServerPort = port;
			if (interval == 0)
			{
				hub->RadiusRetryInterval = RADIUS_RETRY_INTERVAL;
			}
			else if (interval > RADIUS_RETRY_TIMEOUT)
			{
				hub->RadiusRetryInterval = RADIUS_RETRY_TIMEOUT;
			}
			else
			{
				hub->RadiusRetryInterval = interval;
			}
			FreeBuf(hub->RadiusSecret);

			if (secret == NULL)
			{
				hub->RadiusSecret = NewBuf();
			}
			else
			{
				hub->RadiusSecret = NewBuf();
				WriteBuf(hub->RadiusSecret, secret, StrLen(secret));
				SeekBuf(hub->RadiusSecret, 0, 0);
			}
		}
	}
	Unlock(hub->RadiusOptionLock);
}