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

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 int /*<<< orphan*/  PicoWrite16_io (int,int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  carthw_pier_write8 (int,int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carthw_pier_write16(u32 a, u32 d)
{
  if ((a & 0xffff00) != 0xa13000) {
    PicoWrite16_io(a, d);
    return;
  }

  elprintf(EL_UIO, "pier w16 [%06x] %04x @%06x", a, d & 0xffff, SekPc);
  carthw_pier_write8(a + 1, d);
}