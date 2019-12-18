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
typedef  int /*<<< orphan*/  PSDevice ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestIn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MESSAGE_TYPE_READ ; 

void ControlvReadByte(PSDevice pDevice, BYTE byRegType, BYTE byRegOfs, PBYTE pbyData)
{
NTSTATUS        ntStatus;
BYTE            byData1;


    ntStatus = CONTROLnsRequestIn(pDevice,
                                    MESSAGE_TYPE_READ,
                                    byRegOfs,
                                    byRegType,
                                    1,
                                    &byData1);

    *pbyData = byData1;

}