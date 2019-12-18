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
typedef  int /*<<< orphan*/  drbuf ;

/* Variables and functions */
 scalar_t__ ISPIPE ; 
 int MAXBLK ; 
 int /*<<< orphan*/  arfd ; 
 scalar_t__ artyp ; 
 int lstrval ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

void
ar_drain(void)
{
	int res;
	char drbuf[MAXBLK];

	/*
	 * we only drain from a pipe/socket. Other devices can be closed
	 * without reading up to end of file. We sure hope that pipe is closed
	 * on the other side so we will get an EOF.
	 */
	if ((artyp != ISPIPE) || (lstrval <= 0))
		return;

	/*
	 * keep reading until pipe is drained
	 */
	while ((res = read(arfd, drbuf, sizeof(drbuf))) > 0)
		;
	lstrval = res;
}