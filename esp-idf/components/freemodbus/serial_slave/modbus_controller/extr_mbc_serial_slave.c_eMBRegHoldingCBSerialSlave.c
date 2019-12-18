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
typedef  int eMBRegisterMode ;
typedef  int /*<<< orphan*/  eMBErrorCode ;
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {TYPE_2__ opts; } ;
struct TYPE_4__ {int size; scalar_t__ address; scalar_t__ start_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_EINVAL ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int /*<<< orphan*/  MB_ENOREG ; 
 int /*<<< orphan*/  MB_EVENT_HOLDING_REG_RD ; 
 int /*<<< orphan*/  MB_EVENT_HOLDING_REG_WR ; 
 size_t MB_PARAM_HOLDING ; 
#define  MB_REG_READ 129 
#define  MB_REG_WRITE 128 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _XFER_2_RD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _XFER_2_WR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* mbs_interface_ptr ; 
 int /*<<< orphan*/  send_param_access_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_param_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

eMBErrorCode eMBRegHoldingCBSerialSlave(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNRegs, eMBRegisterMode eMode)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL), 
                    MB_EILLSTATE, "Slave stack uninitialized.");
    MB_SLAVE_CHECK((pucRegBuffer != NULL), 
                    MB_EINVAL, "Slave stack call failed.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    USHORT usRegHoldingNregs = (USHORT)(mbs_opts->mbs_area_descriptors[MB_PARAM_HOLDING].size >> 1);
    USHORT usRegHoldingStart = (USHORT)mbs_opts->mbs_area_descriptors[MB_PARAM_HOLDING].start_offset;
    UCHAR* pucHoldingBuffer = (UCHAR*)mbs_opts->mbs_area_descriptors[MB_PARAM_HOLDING].address;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegIndex;
    USHORT usRegs = usNRegs;
    // Check input and configuration parameters for correctness
    if ((usAddress >= usRegHoldingStart)
            && (pucHoldingBuffer != NULL)
            && ((usAddress + usRegs) <= (usRegHoldingStart + usRegHoldingNregs + 1))
            && (usRegHoldingNregs >= 1)
            && (usNRegs >= 1)) {
        iRegIndex = (USHORT) (usAddress - usRegHoldingStart - 1);
        iRegIndex <<= 1; // register Address to byte address
        pucHoldingBuffer += iRegIndex;
        UCHAR* pucBufferStart = pucHoldingBuffer;
        switch (eMode) {
            case MB_REG_READ:
                while (usRegs > 0) {
                    _XFER_2_RD(pucRegBuffer, pucHoldingBuffer);
                    iRegIndex += 2;
                    usRegs -= 1;
                };
                // Send access notification
                (void)send_param_access_notification(MB_EVENT_HOLDING_REG_RD);
                // Send parameter info
                (void)send_param_info(MB_EVENT_HOLDING_REG_RD, (uint16_t)usAddress,
                                (uint8_t*)pucBufferStart, (uint16_t)usNRegs);
                break;
            case MB_REG_WRITE:
                while (usRegs > 0) {
                    _XFER_2_WR(pucHoldingBuffer, pucRegBuffer);
                    pucHoldingBuffer += 2;
                    iRegIndex += 2;
                    usRegs -= 1;
                };
                // Send access notification
                (void)send_param_access_notification(MB_EVENT_HOLDING_REG_WR);
                // Send parameter info
                (void)send_param_info(MB_EVENT_HOLDING_REG_WR, (uint16_t)usAddress,
                                (uint8_t*)pucBufferStart, (uint16_t)usNRegs);
                break;
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}