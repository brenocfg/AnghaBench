#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mbm_reg_buffer_ptr; int /*<<< orphan*/  mbm_reg_buffer_size; } ;
typedef  TYPE_1__ mb_master_options_t ;
typedef  int /*<<< orphan*/  eMBErrorCode ;
typedef  int USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EILLSTATE ; 
 int /*<<< orphan*/  MB_EINVAL ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int /*<<< orphan*/  MB_ENOREG ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _XFER_2_RD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* mbm_interface_ptr ; 

eMBErrorCode eMBRegInputCBSerialMaster(UCHAR * pucRegBuffer, USHORT usAddress,
                                USHORT usNRegs)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    MB_EILLSTATE,
                    "Master interface uninitialized.");
    MB_MASTER_CHECK((pucRegBuffer != NULL), MB_EINVAL,
                    "Master stack processing error.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    // Number of input registers to be transferred
    USHORT usRegInputNregs = (USHORT)mbm_opts->mbm_reg_buffer_size; 
    UCHAR* pucInputBuffer = (UCHAR*)mbm_opts->mbm_reg_buffer_ptr; // Get instance address
    USHORT usRegs = usNRegs;
    eMBErrorCode eStatus = MB_ENOERR;
    // If input or configuration parameters are incorrect then return an error to stack layer
    if ((pucInputBuffer != NULL)
            && (usNRegs >= 1)
            && (usRegInputNregs == usRegs)) {
        while (usRegs > 0) {
            _XFER_2_RD(pucInputBuffer, pucRegBuffer);
            usRegs -= 1;
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}