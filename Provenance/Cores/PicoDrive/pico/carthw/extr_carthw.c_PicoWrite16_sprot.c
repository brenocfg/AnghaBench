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
 int /*<<< orphan*/  EL_UIO ; 
 int /*<<< orphan*/  PicoWrite16_io (int,int) ; 
 int /*<<< orphan*/  SekPc ; 
 int* carthw_sprot_get_val (int,int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWrite16_sprot(u32 a, u32 d)
{
  u16 *val;

  if (0xa10000 <= a && a < 0xa12000) {
    PicoWrite16_io(a, d);
    return;
  }

  val = carthw_sprot_get_val(a, 1);
  if (val != NULL) {
    *val = d;
    elprintf(EL_UIO, "prot w16 [%06x] %04x @%06x", a, d & 0xffff, SekPc);
  }
  else
    elprintf(EL_UIO, "prot w16 [%06x] %04x MISS @%06x", a, d & 0xffff, SekPc);
}