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
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_NOTIFY_PORT ; 
 int /*<<< orphan*/ * ConnectEx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCK *CncConnectEx(UINT timeout)
{
	SOCK *s = ConnectEx("localhost", CLIENT_NOTIFY_PORT, timeout);

	return s;
}