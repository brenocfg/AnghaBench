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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnCFG_BBType_MASK ; 
 int /*<<< orphan*/  MAC_REG_ENCFG0 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE_MASK ; 

void MACvSetBBType(PSDevice pDevice,BYTE byType)
{
BYTE            pbyData[2];


    pbyData[0] = byType;
    pbyData[1] = EnCFG_BBType_MASK;

    CONTROLnsRequestOut(pDevice,
                        MESSAGE_TYPE_WRITE_MASK,
                        MAC_REG_ENCFG0,
                        MESSAGE_REQUEST_MACREG,
                        2,
                        pbyData
                        );
}