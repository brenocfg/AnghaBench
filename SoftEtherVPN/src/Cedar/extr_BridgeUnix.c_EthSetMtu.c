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
struct lifreq {int dummy; } ;
struct ifreq {int lifr_mtu; int ifr_mtu; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  lifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int UINT ;
struct TYPE_3__ {int InitialMtu; int SocketBsdIf; int Socket; int CurrentMtu; int /*<<< orphan*/  Name; scalar_t__ IsRawIpMode; int /*<<< orphan*/ * Tap; } ;
typedef  TYPE_1__ ETH ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  SIOCSLIFMTU ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (struct ifreq*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 

bool EthSetMtu(ETH *e, UINT mtu)
{
#if	defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	UINT ret = 0;
#ifdef	UNIX_SOLARIS
	struct lifreq ifr;
#else	// UNIX_SOLARIS
	struct ifreq ifr;
#endif	// UNIX_SOLARIS
	int s;
	// Validate arguments
	if (e == NULL || e->Tap != NULL || (mtu > 1 && mtu < 1514))
	{
		return false;
	}
	if (mtu == 0 && e->InitialMtu == 0)
	{
		return false;
	}
	if (e->IsRawIpMode)
	{
		return false;
	}

	if (mtu == 0)
	{
		// Restore initial MTU value when parameter mtu == 0
		mtu = e->InitialMtu;
	}

#if	defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	s = e->SocketBsdIf;
#else	// defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	s = e->Socket;
#endif	// defined(UNIX_BSD) || defined(UNIX_SOLARIS)

	if (e->CurrentMtu == mtu)
	{
		// No need to change
		return true;
	}

	Zero(&ifr, sizeof(ifr));

#ifdef	UNIX_SOLARIS
	StrCpy(ifr.lifr_name, sizeof(ifr.lifr_name), e->Name);
	ifr.lifr_mtu = mtu - 14;
#else	// UNIX_SOLARIS
	StrCpy(ifr.ifr_name, sizeof(ifr.ifr_name), e->Name);
	ifr.ifr_mtu = mtu - 14;
#endif	// UNIX_SOLARIS

#ifdef	UNIX_SOLARIS
	if (ioctl(s, SIOCSLIFMTU, &ifr) < 0)
	{
		// Failed
		return false;
	}
#else	// UNIX_SOLARIS
	if (ioctl(s, SIOCSIFMTU, &ifr) < 0)
	{
		// Failed
		return false;
	}
#endif	// UNIX_SOLARIS

	e->CurrentMtu = mtu;

	Debug("%s: SetMtu: %u\n", e->Name, mtu);

	return true;
#else	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	return false;
#endif	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
}