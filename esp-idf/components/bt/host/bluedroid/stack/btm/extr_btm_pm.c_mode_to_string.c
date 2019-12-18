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
typedef  int tBTM_PM_MODE ;

/* Variables and functions */
#define  BTM_PM_MD_ACTIVE 131 
#define  BTM_PM_MD_HOLD 130 
#define  BTM_PM_MD_PARK 129 
#define  BTM_PM_MD_SNIFF 128 

__attribute__((used)) static const char *mode_to_string(tBTM_PM_MODE mode)
{
    switch (mode) {
    case BTM_PM_MD_ACTIVE: return "ACTIVE";
    case BTM_PM_MD_SNIFF:  return "SNIFF";
    case BTM_PM_MD_PARK:   return "PARK";
    case BTM_PM_MD_HOLD:   return "HOLD";
    default:               return "UNKNOWN";
    }
}