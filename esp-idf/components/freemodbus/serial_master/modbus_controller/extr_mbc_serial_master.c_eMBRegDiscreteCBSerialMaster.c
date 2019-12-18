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
struct TYPE_3__ {scalar_t__ mbm_reg_buffer_ptr; scalar_t__ mbm_reg_buffer_size; } ;
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
 TYPE_2__* mbm_interface_ptr ; 
 int /*<<< orphan*/  xMBUtilSetBits (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

eMBErrorCode eMBRegDiscreteCBSerialMaster(UCHAR * pucRegBuffer, USHORT usAddress,
                            USHORT usNDiscrete)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    MB_EILLSTATE, "Master interface uninitialized.");
    MB_MASTER_CHECK((pucRegBuffer != NULL), 
                    MB_EINVAL, "Master stack processing error.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    USHORT usRegDiscreteNregs = (USHORT)mbm_opts->mbm_reg_buffer_size;
    UCHAR* pucRegDiscreteBuf = (UCHAR*)mbm_opts->mbm_reg_buffer_ptr;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegBitIndex, iNReg;
    UCHAR* pucDiscreteInputBuf;
    iNReg = usNDiscrete / 8 + 1;
    pucDiscreteInputBuf = (UCHAR*) pucRegDiscreteBuf;
    // It is already plus one in Modbus function method.
    usAddress--;
    if ((usRegDiscreteNregs >= 1)
            && (pucRegDiscreteBuf != NULL)
            && (usNDiscrete >= 1)) {
        iRegBitIndex = (USHORT)(usAddress) % 8; // Get bit index
        while (iNReg > 1)
        {
            xMBUtilSetBits(pucDiscreteInputBuf++, iRegBitIndex, 8, *pucRegBuffer++);
            iNReg--;
        }
        // last discrete
        usNDiscrete = usNDiscrete % 8;
        // xMBUtilSetBits has bug when ucNBits is zero
        if (usNDiscrete != 0)
        {
            xMBUtilSetBits(pucDiscreteInputBuf, iRegBitIndex, usNDiscrete, *pucRegBuffer++);
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}