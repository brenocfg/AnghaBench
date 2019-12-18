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
#define  IA64_RS_ARX 130 
#define  IA64_RS_CRX 129 
#define  IA64_RS_PSR 128 
 int REG_NONE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static int
lookup_regindex (const char *name, int specifier)
{
  switch (specifier)
    {
    case IA64_RS_ARX:
      if (strstr (name, "[RSC]"))
        return 16;
      if (strstr (name, "[BSP]"))
        return 17;
      else if (strstr (name, "[BSPSTORE]"))
        return 18;
      else if (strstr (name, "[RNAT]"))
        return 19;
      else if (strstr (name, "[FCR]"))
        return 21;
      else if (strstr (name, "[EFLAG]"))
        return 24;
      else if (strstr (name, "[CSD]"))
        return 25;
      else if (strstr (name, "[SSD]"))
        return 26;
      else if (strstr (name, "[CFLG]"))
        return 27;
      else if (strstr (name, "[FSR]"))
        return 28;
      else if (strstr (name, "[FIR]"))
        return 29;
      else if (strstr (name, "[FDR]"))
        return 30;
      else if (strstr (name, "[CCV]"))
        return 32;
      else if (strstr (name, "[ITC]"))
        return 44;
      else if (strstr (name, "[PFS]"))
        return 64;
      else if (strstr (name, "[LC]"))
        return 65;
      else if (strstr (name, "[EC]"))
        return 66;
      abort ();
    case IA64_RS_CRX:
      if (strstr (name, "[DCR]"))
        return 0;
      else if (strstr (name, "[ITM]"))
        return 1;
      else if (strstr (name, "[IVA]"))
        return 2;
      else if (strstr (name, "[PTA]"))
        return 8;
      else if (strstr (name, "[GPTA]"))
        return 9;
      else if (strstr (name, "[IPSR]"))
        return 16;
      else if (strstr (name, "[ISR]"))
        return 17;
      else if (strstr (name, "[IIP]"))
        return 19;
      else if (strstr (name, "[IFA]"))
        return 20;
      else if (strstr (name, "[ITIR]"))
        return 21;
      else if (strstr (name, "[IIPA]"))
        return 22;
      else if (strstr (name, "[IFS]"))
        return 23;
      else if (strstr (name, "[IIM]"))
        return 24;
      else if (strstr (name, "[IHA]"))
        return 25;
      else if (strstr (name, "[LID]"))
        return 64;
      else if (strstr (name, "[IVR]"))
        return 65;
      else if (strstr (name, "[TPR]"))
        return 66;
      else if (strstr (name, "[EOI]"))
        return 67;
      else if (strstr (name, "[ITV]"))
        return 72;
      else if (strstr (name, "[PMV]"))
        return 73;
      else if (strstr (name, "[CMCV]"))
        return 74;
      abort ();
    case IA64_RS_PSR:
      if (strstr (name, ".be"))
        return 1;
      else if (strstr (name, ".up"))
        return 2;
      else if (strstr (name, ".ac"))
        return 3;
      else if (strstr (name, ".mfl"))
        return 4;
      else if (strstr (name, ".mfh"))
        return 5;
      else if (strstr (name, ".ic"))
        return 13;
      else if (strstr (name, ".i"))
        return 14;
      else if (strstr (name, ".pk"))
        return 15;
      else if (strstr (name, ".dt"))
        return 17;
      else if (strstr (name, ".dfl"))
        return 18;
      else if (strstr (name, ".dfh"))
        return 19;
      else if (strstr (name, ".sp"))
        return 20;
      else if (strstr (name, ".pp"))
        return 21;
      else if (strstr (name, ".di"))
        return 22;
      else if (strstr (name, ".si"))
        return 23;
      else if (strstr (name, ".db"))
        return 24;
      else if (strstr (name, ".lp"))
        return 25;
      else if (strstr (name, ".tb"))
        return 26;
      else if (strstr (name, ".rt"))
        return 27;
      else if (strstr (name, ".cpl"))
        return 32;
      else if (strstr (name, ".rs"))
        return 34;
      else if (strstr (name, ".mc"))
        return 35;
      else if (strstr (name, ".it"))
        return 36;
      else if (strstr (name, ".id"))
        return 37;
      else if (strstr (name, ".da"))
        return 38;
      else if (strstr (name, ".dd"))
        return 39;
      else if (strstr (name, ".ss"))
        return 40;
      else if (strstr (name, ".ri"))
        return 41;
      else if (strstr (name, ".ed"))
        return 43;
      else if (strstr (name, ".bn"))
        return 44;
      else if (strstr (name, ".ia"))
        return 45;
      else if (strstr (name, ".vm"))
        return 46;
      else
        abort ();
    default:
      break;
    }
  return REG_NONE;
}