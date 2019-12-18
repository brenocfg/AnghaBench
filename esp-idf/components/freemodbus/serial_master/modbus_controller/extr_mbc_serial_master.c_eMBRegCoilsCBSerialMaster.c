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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ mbm_reg_buffer_ptr; int /*<<< orphan*/  mbm_reg_buffer_size; } ;
typedef  TYPE_1__ mb_master_options_t ;
typedef  int eMBRegisterMode ;
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
#define  MB_REG_READ 129 
#define  MB_REG_WRITE 128 
 TYPE_2__* mbm_interface_ptr ; 
 int /*<<< orphan*/  xMBUtilGetBits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  xMBUtilSetBits (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

eMBErrorCode eMBRegCoilsCBSerialMaster(UCHAR* pucRegBuffer, USHORT usAddress,
        USHORT usNCoils, eMBRegisterMode eMode)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    MB_EILLSTATE, "Master interface uninitialized.");
    MB_MASTER_CHECK((pucRegBuffer != NULL), 
                    MB_EINVAL, "Master stack processing error.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    USHORT usRegCoilNregs = (USHORT)mbm_opts->mbm_reg_buffer_size;
    UCHAR* pucRegCoilsBuf = (UCHAR*)mbm_opts->mbm_reg_buffer_ptr;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegIndex;
    USHORT usCoils = usNCoils;
    usAddress--; // The address is already + 1
    if ((usRegCoilNregs >= 1)
            && (pucRegCoilsBuf != NULL)
            && (usNCoils == usRegCoilNregs)) {
        iRegIndex = (usAddress % 8);
        switch (eMode) {
            case MB_REG_WRITE:
                while (usCoils > 0) {
                    UCHAR ucResult = xMBUtilGetBits((UCHAR*)pucRegCoilsBuf, iRegIndex, 1);
                    xMBUtilSetBits(pucRegBuffer, iRegIndex - (usAddress % 8) , 1, ucResult);
                    iRegIndex++;
                    usCoils--;
                }
                break;
            case MB_REG_READ:
                while (usCoils > 0) {
                    UCHAR ucResult = xMBUtilGetBits(pucRegBuffer, iRegIndex - (usAddress % 8), 1);
                    xMBUtilSetBits((uint8_t*)pucRegCoilsBuf, iRegIndex, 1, ucResult);
                    iRegIndex++;
                    usCoils--;
                }
                break;
        } // switch ( eMode )
    } else {
        // If the configuration or input parameters are incorrect then return error to stack
        eStatus = MB_ENOREG;
    }
    return eStatus;
}