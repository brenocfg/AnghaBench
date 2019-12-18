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
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int MAC_MAX_CONTEXT_SIZE_PAGE0 ; 
 int MAC_MAX_CONTEXT_SIZE_PAGE1 ; 
 int /*<<< orphan*/  MACbSoftwareReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRestoreContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MACvSaveContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOL MACbSafeSoftwareReset (DWORD_PTR dwIoBase)
{
    BYTE    abyTmpRegData[MAC_MAX_CONTEXT_SIZE_PAGE0+MAC_MAX_CONTEXT_SIZE_PAGE1];
    BOOL    bRetVal;

    // PATCH....
    // save some important register's value, then do
    // reset, then restore register's value

    // save MAC context
    MACvSaveContext(dwIoBase, abyTmpRegData);
    // do reset
    bRetVal = MACbSoftwareReset(dwIoBase);
    //BBvSoftwareReset(pDevice->PortOffset);
    // restore MAC context, except CR0
    MACvRestoreContext(dwIoBase, abyTmpRegData);

    return bRetVal;
}