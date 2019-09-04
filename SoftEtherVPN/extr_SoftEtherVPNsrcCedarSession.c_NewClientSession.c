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
typedef  int /*<<< orphan*/  SESSION ;
typedef  int /*<<< orphan*/  PACKET_ADAPTER ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * NewClientSessionEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

SESSION *NewClientSession(CEDAR *cedar, CLIENT_OPTION *option, CLIENT_AUTH *auth, PACKET_ADAPTER *pa, bool *NicDownOnDisconnect)
{
	return NewClientSessionEx(cedar, option, auth, pa, NULL, NicDownOnDisconnect);
}