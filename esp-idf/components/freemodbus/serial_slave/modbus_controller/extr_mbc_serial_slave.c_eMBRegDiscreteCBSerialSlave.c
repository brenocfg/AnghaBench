#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_1__* mbs_area_descriptors; } ;
typedef  TYPE_2__ mb_slave_options_t ;
typedef  int /*<<< orphan*/  eMBErrorCode ;
typedef  int USHORT ;
typedef  int UCHAR ;
struct TYPE_6__ {TYPE_2__ opts; } ;
struct TYPE_4__ {int size; scalar_t__ address; scalar_t__ start_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_EINVAL ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int /*<<< orphan*/  MB_ENOREG ; 
 int /*<<< orphan*/  MB_EVENT_DISCRETE_RD ; 
 size_t MB_PARAM_DISCRETE ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* mbs_interface_ptr ; 
 int /*<<< orphan*/  send_param_access_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_param_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMBUtilGetBits (int*,int,int) ; 

eMBErrorCode eMBRegDiscreteCBSerialSlave(UCHAR* pucRegBuffer, USHORT usAddress,
                            USHORT usNDiscrete)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL), 
                    MB_EILLSTATE, "Slave stack uninitialized.");
    MB_SLAVE_CHECK((pucRegBuffer != NULL), 
                    MB_EINVAL, "Slave stack call failed.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    USHORT usRegDiscreteNregs = (USHORT)(mbs_opts->mbs_area_descriptors[MB_PARAM_DISCRETE].size >> 1); // number of registers in storage area
    USHORT usRegDiscreteStart = (USHORT)mbs_opts->mbs_area_descriptors[MB_PARAM_DISCRETE].start_offset; // MB offset of registers
    UCHAR* pucRegDiscreteBuf = (UCHAR*)mbs_opts->mbs_area_descriptors[MB_PARAM_DISCRETE].address; // the storage address
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegIndex, iRegBitIndex, iNReg;
    UCHAR* pucDiscreteInputBuf;
    iNReg = usNDiscrete / 8 + 1;
    pucDiscreteInputBuf = (UCHAR*) pucRegDiscreteBuf;
    // It already plus one in modbus function method.
    usAddress--;
    if ((usAddress >= usRegDiscreteStart)
            && (usRegDiscreteNregs >= 1)
            && (pucRegDiscreteBuf != NULL)
            && ((usAddress + usNDiscrete) <= (usRegDiscreteStart + (usRegDiscreteNregs * 16)))
            && (usNDiscrete >= 1)) {
        iRegIndex = (USHORT) (usAddress - usRegDiscreteStart) / 8; // Get register index in the buffer for bit number
        iRegBitIndex = (USHORT)(usAddress - usRegDiscreteStart) % 8; // Get bit index
        UCHAR* pucTempBuf = &pucDiscreteInputBuf[iRegIndex];
        while (iNReg > 0) {
            *pucRegBuffer++ = xMBUtilGetBits(&pucDiscreteInputBuf[iRegIndex++], iRegBitIndex, 8);
            iNReg--;
        }
        pucRegBuffer--;
        // Last discrete
        usNDiscrete = usNDiscrete % 8;
        // Filling zero to high bit
        *pucRegBuffer = *pucRegBuffer << (8 - usNDiscrete);
        *pucRegBuffer = *pucRegBuffer >> (8 - usNDiscrete);
        // Send an event to notify application task about event
        (void)send_param_access_notification(MB_EVENT_DISCRETE_RD);
        (void)send_param_info(MB_EVENT_DISCRETE_RD, (uint16_t)usAddress,
                            (uint8_t*)pucTempBuf, (uint16_t)usNDiscrete);
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}