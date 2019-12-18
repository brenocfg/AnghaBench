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
typedef  char gchar ;

/* Variables and functions */
 size_t fARCH_aarch64 ; 
 size_t fARCH_arm ; 
 size_t fARCH_i386 ; 
 size_t fARCH_x86_64 ; 

gchar* getArchName(bool* archs) {
    if (archs[fARCH_i386])
        return "i386";
    else if (archs[fARCH_x86_64])
        return "x86_64";
    else if (archs[fARCH_arm])
        return "armhf";
    else if (archs[fARCH_aarch64])
        return "aarch64";
    else
        return "all";
}