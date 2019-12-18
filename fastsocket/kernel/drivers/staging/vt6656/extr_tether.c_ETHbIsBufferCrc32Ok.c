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
typedef  int UINT ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int PBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CRCdwGetCrc32 (int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

BOOL ETHbIsBufferCrc32Ok (PBYTE pbyBuffer, UINT cbFrameLength)
{
    DWORD dwCRC;

    dwCRC = CRCdwGetCrc32(pbyBuffer, cbFrameLength - 4);
    if (cpu_to_le32(*((PDWORD)(pbyBuffer + cbFrameLength - 4))) != dwCRC) {
        return FALSE;
    }
    return TRUE;
}