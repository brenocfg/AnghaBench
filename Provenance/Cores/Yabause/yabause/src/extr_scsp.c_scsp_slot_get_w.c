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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  new_scsp ; 
 int /*<<< orphan*/ * scsp_isr ; 
 int scsp_slot_read_word (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u16 scsp_slot_get_w(u32 s, u32 a)
{
#ifdef USE_NEW_SCSP
  return scsp_slot_read_word(&new_scsp, a);
#endif
  u16 val = *(u16 *)&scsp_isr[a ^ 2];

  if ((a & 0x1E) == 0x00) return val &= 0xEFFF;

  SCSPLOG ("r_w slot %d (%.2X) : reg %.2X = %.4X\n", s, a, a & 0x1E, val);

  return val;
}