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
typedef  int WORD ;
typedef  int /*<<< orphan*/  PSDevice ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 

void MACvWriteWord(PSDevice pDevice, BYTE byRegOfs, WORD wData)
{
BYTE            pbyData[2];


    pbyData[0] = (BYTE)(wData & 0xff);
    pbyData[1] = (BYTE)(wData >> 8);

    CONTROLnsRequestOut(pDevice,
                        MESSAGE_TYPE_WRITE,
                        byRegOfs,
                        MESSAGE_REQUEST_MACREG,
                        2,
                        pbyData
                        );

}