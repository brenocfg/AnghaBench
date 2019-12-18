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

__attribute__((used)) static const char *
psr_name (int regno)
{
  switch (regno)
    {
    case 0: return "APSR";
    case 1: return "IAPSR";
    case 2: return "EAPSR";
    case 3: return "PSR";
    case 5: return "IPSR";
    case 6: return "EPSR";
    case 7: return "IEPSR";
    case 8: return "MSP";
    case 9: return "PSP";
    case 16: return "PRIMASK";
    case 17: return "BASEPRI";
    case 18: return "BASEPRI_MASK";
    case 19: return "FAULTMASK";
    case 20: return "CONTROL";
    default: return "<unknown>";
    }
}