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
typedef  scalar_t__ PDWORD ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  SROMbyReadEmbedded (int /*<<< orphan*/ ,int) ; 

void SROMvReadSubSysVenId (DWORD_PTR dwIoBase, PDWORD pdwSubSysVenId)
{
    PBYTE   pbyData;

    pbyData = (PBYTE)pdwSubSysVenId;
    // sub vendor
    *pbyData = SROMbyReadEmbedded(dwIoBase, 6);
    *(pbyData+1) = SROMbyReadEmbedded(dwIoBase, 7);
    // sub system
    *(pbyData+2) = SROMbyReadEmbedded(dwIoBase, 8);
    *(pbyData+3) = SROMbyReadEmbedded(dwIoBase, 9);
}