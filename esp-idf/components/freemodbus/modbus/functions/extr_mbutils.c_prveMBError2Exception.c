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
typedef  int /*<<< orphan*/  eMBException ;
typedef  int eMBErrorCode ;

/* Variables and functions */
#define  MB_ENOERR 130 
#define  MB_ENOREG 129 
#define  MB_ETIMEDOUT 128 
 int /*<<< orphan*/  MB_EX_ILLEGAL_DATA_ADDRESS ; 
 int /*<<< orphan*/  MB_EX_NONE ; 
 int /*<<< orphan*/  MB_EX_SLAVE_BUSY ; 
 int /*<<< orphan*/  MB_EX_SLAVE_DEVICE_FAILURE ; 

eMBException
prveMBError2Exception( eMBErrorCode eErrorCode )
{
    eMBException    eStatus;

    switch ( eErrorCode )
    {
        case MB_ENOERR:
            eStatus = MB_EX_NONE;
            break;

        case MB_ENOREG:
            eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
            break;

        case MB_ETIMEDOUT:
            eStatus = MB_EX_SLAVE_BUSY;
            break;

        default:
            eStatus = MB_EX_SLAVE_DEVICE_FAILURE;
            break;
    }

    return eStatus;
}