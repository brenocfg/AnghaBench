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

/* Variables and functions */
 int AV_CPU_FLAG_ARMV8 ; 
 int AV_CPU_FLAG_NEON ; 
 int AV_CPU_FLAG_VFP ; 
 int HAVE_ARMV8 ; 
 int HAVE_NEON ; 
 int HAVE_VFP ; 

int ff_get_cpu_flags_aarch64(void)
{
    return AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
           AV_CPU_FLAG_NEON  * HAVE_NEON  |
           AV_CPU_FLAG_VFP   * HAVE_VFP;
}