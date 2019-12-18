#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int coefdatasize; int msb; } ;
typedef  TYPE_1__ vdp2rotationparameter_struct ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int T1ReadLong (int /*<<< orphan*/ *,int) ; 
 int T1ReadWord (int /*<<< orphan*/ *,int) ; 

float Vdp2ReadCoefficientMode0_2(vdp2rotationparameter_struct *parameter, u32 addr, u8 * ram)
{
   s32 i;

   if (parameter->coefdatasize == 2)
   {
      addr &= 0x7FFFE;
      i = T1ReadWord(ram, addr);
      parameter->msb = (i >> 15) & 0x1;
      return (float) (signed) ((i & 0x7FFF) | (i & 0x4000 ? 0xFFFFC000 : 0x00000000)) / 1024;
   }
   else
   {
      addr &= 0x7FFFC;
      i = T1ReadLong(ram, addr);
      parameter->msb = (i >> 31) & 0x1;
      return (float) (signed) ((i & 0x00FFFFFF) | (i & 0x00800000 ? 0xFF800000 : 0x00000000)) / 65536;
   }
}