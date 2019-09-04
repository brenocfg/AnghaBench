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
struct TYPE_3__ {int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_DELETE_DEVICE ;
typedef  int /*<<< orphan*/  EL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CAPTURE_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int ElDeleteCaptureDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ElSaveConfig (int /*<<< orphan*/ *) ; 

UINT EtDelDevice(EL *e, RPC_DELETE_DEVICE *t)
{
	if (ElDeleteCaptureDevice(e, t->DeviceName) == false)
	{
		return ERR_CAPTURE_NOT_FOUND;
	}

	ElSaveConfig(e);

	return ERR_NO_ERROR;
}