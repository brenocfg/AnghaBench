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
struct SiS_Private {int /*<<< orphan*/  SiS_P3da; } ;

/* Variables and functions */
 unsigned short SiS_GetRegByte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SiS_VBWait(struct SiS_Private *SiS_Pr)
{
   unsigned short tempal,temp,i,j;

   temp = 0;
   for(i = 0; i < 3; i++) {
     for(j = 0; j < 100; j++) {
        tempal = SiS_GetRegByte(SiS_Pr->SiS_P3da);
        if(temp & 0x01) {
	   if((tempal & 0x08))  continue;
	   else break;
        } else {
	   if(!(tempal & 0x08)) continue;
	   else break;
        }
     }
     temp ^= 0x01;
   }
}