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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  ETH ;

/* Variables and functions */

UINT EthGetMtu(ETH *e)
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
	if (e == NULL || e->Tap != NULL)
	{
		return 0;
	}
	if (e->IsRawIpMode)
	{
		return 0;
	}

	if (e->CurrentMtu != 0)
	{
		return e->CurrentMtu;
	}

#if	defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	s = e->SocketBsdIf;
#else	// defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	s = e->Socket;
#endif	// defined(UNIX_BSD) || defined(UNIX_SOLARIS)

	Zero(&ifr, sizeof(ifr));

#ifdef	UNIX_SOLARIS
	StrCpy(ifr.lifr_name, sizeof(ifr.lifr_name), e->Name);
#else	// UNIX_SOLARIS
	StrCpy(ifr.ifr_name, sizeof(ifr.ifr_name), e->Name);
#endif	// UNIX_SOLARIS

#ifdef	UNIX_SOLARIS
	if (ioctl(s, SIOCGLIFMTU, &ifr) < 0)
	{
		// failed
		return 0;
	}
#else	// UNIX_SOLARIS
	if (ioctl(s, SIOCGIFMTU, &ifr) < 0)
	{
		// failed
		return 0;
	}
#endif	// UNIX_SOLARIS

#ifdef	UNIX_SOLARIS
	ret = ifr.lifr_mtu + 14;
#else	// UNIX_SOLARIS
	ret = ifr.ifr_mtu + 14;
#endif	// UNIX_SOLARIS

	e->CurrentMtu = ret;

	Debug("%s: GetMtu: %u\n", e->Name, ret);

	return ret;
#else	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	return 0;
#endif	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
}