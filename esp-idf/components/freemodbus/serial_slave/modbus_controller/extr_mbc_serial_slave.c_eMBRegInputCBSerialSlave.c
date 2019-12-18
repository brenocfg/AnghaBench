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
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {TYPE_2__ opts; } ;
struct TYPE_4__ {int size; scalar_t__ address; scalar_t__ start_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_EINVAL ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int /*<<< orphan*/  MB_ENOREG ; 
 int /*<<< orphan*/  MB_EVENT_INPUT_REG_RD ; 
 size_t MB_PARAM_INPUT ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _XFER_2_RD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* mbs_interface_ptr ; 
 int /*<<< orphan*/  send_param_access_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_param_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

eMBErrorCode eMBRegInputCBSerialSlave(UCHAR * pucRegBuffer, USHORT usAddress,
                                USHORT usNRegs)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL), 
                    MB_EILLSTATE, "Slave stack uninitialized.");
    MB_SLAVE_CHECK((pucRegBuffer != NULL), 
                    MB_EINVAL, "Slave stack call failed.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    USHORT usRegInputNregs = (USHORT)(mbs_opts->mbs_area_descriptors[MB_PARAM_INPUT].size >> 1); // Number of input registers
    USHORT usInputRegStart = (USHORT)mbs_opts->mbs_area_descriptors[MB_PARAM_INPUT].start_offset; // Get Modbus start address
    UCHAR* pucInputBuffer = (UCHAR*)mbs_opts->mbs_area_descriptors[MB_PARAM_INPUT].address; // Get instance address
    USHORT usRegs = usNRegs;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegIndex;
    // If input or configuration parameters are incorrect then return an error to stack layer
    if ((usAddress >= usInputRegStart)
            && (pucInputBuffer != NULL)
            && (usNRegs >= 1)
            && ((usAddress + usRegs) <= (usInputRegStart + usRegInputNregs + 1))
            && (usRegInputNregs >= 1)) {
        iRegIndex = (USHORT)(usAddress - usInputRegStart - 1);
        iRegIndex <<= 1; // register Address to byte address
        pucInputBuffer += iRegIndex;
        UCHAR* pucBufferStart = pucInputBuffer;
        while (usRegs > 0) {
            _XFER_2_RD(pucRegBuffer, pucInputBuffer);
            iRegIndex += 2;
            usRegs -= 1;
        }
        // Send access notification
        (void)send_param_access_notification(MB_EVENT_INPUT_REG_RD);
        // Send parameter info to application task
        (void)send_param_info(MB_EVENT_INPUT_REG_RD, (uint16_t)usAddress,
                        (uint8_t*)pucBufferStart, (uint16_t)usNRegs);
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}