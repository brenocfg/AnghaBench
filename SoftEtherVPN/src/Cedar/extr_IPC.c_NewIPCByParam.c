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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Layer; int /*<<< orphan*/  ClientCertificate; int /*<<< orphan*/  Mss; int /*<<< orphan*/  BridgeMode; int /*<<< orphan*/  CryptName; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  Password; int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Postfix; int /*<<< orphan*/  ClientName; } ;
typedef  TYPE_1__ IPC_PARAM ;
typedef  int /*<<< orphan*/  IPC ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * NewIPC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IPC *NewIPCByParam(CEDAR *cedar, IPC_PARAM *param, UINT *error_code)
{
	IPC *ipc;
	// Validate arguments
	if (cedar == NULL || param == NULL)
	{
		return NULL;
	}

	ipc = NewIPC(cedar, param->ClientName, param->Postfix, param->HubName,
		param->UserName, param->Password, error_code, &param->ClientIp,
		param->ClientPort, &param->ServerIp, param->ServerPort,
		param->ClientHostname, param->CryptName,
		param->BridgeMode, param->Mss, NULL, param->ClientCertificate, param->Layer);

	return ipc;
}