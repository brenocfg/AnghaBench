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
typedef  int /*<<< orphan*/  ETH ;

/* Variables and functions */

bool EthIsChangeMtuSupported(ETH *e)
{
#if	defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	// Validate arguments
	if (e == NULL || e->Tap != NULL)
	{
		return false;
	}

	if (e->IsRawIpMode)
	{
		return false;
	}

	return true;
#else	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
	return false;
#endif	// defined(UNIX_LINUX) || defined(UNIX_BSD) || defined(UNIX_SOLARIS)
}