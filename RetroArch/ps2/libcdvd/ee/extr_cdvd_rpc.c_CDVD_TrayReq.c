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

/* Variables and functions */
 int /*<<< orphan*/  CDVD_TRAYREQ ; 
 int /*<<< orphan*/  SifCallRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd0 ; 
 int /*<<< orphan*/  cdvd_inited ; 
 int* sbuff ; 

int CDVD_TrayReq(int mode)
{
    if (!cdvd_inited)
        return -1;

    SifCallRpc(&cd0, CDVD_TRAYREQ, 0, (void *)(&sbuff[0]), 4, (void *)(&sbuff[0]), 4, 0, 0);

    return sbuff[0];
}