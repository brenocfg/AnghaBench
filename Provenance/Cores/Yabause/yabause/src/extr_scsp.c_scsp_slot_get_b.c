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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  new_scsp ; 
 int* scsp_isr ; 
 int scsp_slot_read_byte (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8
scsp_slot_get_b (u32 s, u32 a)
{
#ifdef USE_NEW_SCSP
  return scsp_slot_read_byte(&new_scsp, a);
#endif
  u8 val = scsp_isr[a ^ 3];

  // Mask out keyonx
  if ((a & 0x1F) == 0x00) val &= 0xEF;

  SCSPLOG ("r_b slot %d (%.2X) : reg %.2X = %.2X\n", s, a, a & 0x1F, val);

  return val;
}