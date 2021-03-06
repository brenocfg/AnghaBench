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
struct SiS_Private {int dummy; } ;

/* Variables and functions */
 unsigned short SiS_PrepareReadDDC (struct SiS_Private*) ; 
 scalar_t__ SiS_WriteDABDDC (struct SiS_Private*) ; 

__attribute__((used)) static unsigned short
SiS_PrepareDDC(struct SiS_Private *SiS_Pr)
{
   if(SiS_WriteDABDDC(SiS_Pr)) SiS_WriteDABDDC(SiS_Pr);
   if(SiS_PrepareReadDDC(SiS_Pr)) return (SiS_PrepareReadDDC(SiS_Pr));
   return 0;
}