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
typedef  int /*<<< orphan*/  RPC ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * AdminConnectEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

RPC *AdminConnectEx(CEDAR *cedar, CLIENT_OPTION *o, char *hubname, void *hashed_password, UINT *err, char *client_name)
{
	return AdminConnectEx2(cedar, o, hubname, hashed_password, err, client_name, NULL);
}