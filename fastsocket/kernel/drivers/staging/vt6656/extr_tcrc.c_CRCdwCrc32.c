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
typedef  int /*<<< orphan*/  UINT ;
typedef  int* PBYTE ;
typedef  int DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */
 int* s_adwCrc32Table ; 

DWORD CRCdwCrc32 (PBYTE pbyData, UINT cbByte, DWORD dwCrcSeed)
{
    DWORD dwCrc;

    dwCrc = dwCrcSeed;
    while (cbByte--) {
        dwCrc = s_adwCrc32Table[(BYTE)((dwCrc ^ (*pbyData)) & 0xFF)] ^ (dwCrc >> 8);
        pbyData++;
    }

    return dwCrc;
}