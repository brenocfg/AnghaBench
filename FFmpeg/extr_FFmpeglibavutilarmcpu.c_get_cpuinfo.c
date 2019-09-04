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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HWCAP_EDSP ; 
 int HWCAP_NEON ; 
 int HWCAP_THUMBEE ; 
 int HWCAP_TLS ; 
 int HWCAP_VFP ; 
 int HWCAP_VFPv3 ; 
 scalar_t__ av_strstart (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char buf[200];

    if (!f)
        return -1;

    *hwcap = 0;
    while (fgets(buf, sizeof(buf), f)) {
        if (av_strstart(buf, "Features", NULL)) {
            if (strstr(buf, " edsp "))
                *hwcap |= HWCAP_EDSP;
            if (strstr(buf, " tls "))
                *hwcap |= HWCAP_TLS;
            if (strstr(buf, " thumbee "))
                *hwcap |= HWCAP_THUMBEE;
            if (strstr(buf, " vfp "))
                *hwcap |= HWCAP_VFP;
            if (strstr(buf, " vfpv3 "))
                *hwcap |= HWCAP_VFPv3;
            if (strstr(buf, " neon ") || strstr(buf, " asimd "))
                *hwcap |= HWCAP_NEON;
            if (strstr(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_VFP | HWCAP_VFPv3;
            break;
        }
    }
    fclose(f);
    return 0;
}