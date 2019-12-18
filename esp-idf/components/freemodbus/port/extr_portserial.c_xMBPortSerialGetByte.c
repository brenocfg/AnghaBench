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
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MB_PORT_CHECK (int,int /*<<< orphan*/ ,char*) ; 
 size_t MB_SERIAL_BUF_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucBuffer ; 
 size_t uiRxBufferPos ; 

BOOL xMBPortSerialGetByte(CHAR* pucByte)
{
    assert(pucByte != NULL);
    MB_PORT_CHECK((uiRxBufferPos < MB_SERIAL_BUF_SIZE),
            FALSE, "mb stack serial get byte failure.");
    *pucByte = ucBuffer[uiRxBufferPos];
    uiRxBufferPos++;
    return TRUE;
}