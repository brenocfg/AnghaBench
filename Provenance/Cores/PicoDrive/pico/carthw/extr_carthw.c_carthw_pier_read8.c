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
 int PicoRead8_io (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 carthw_pier_read8(u32 a)
{
  if ((a & 0xffff00) != 0xa13000)
    return PicoRead8_io(a);

  if (a == 0xa1300b)
    return 0; // TODO

  elprintf(EL_UIO, "pier r8  [%06x] @%06x", a, SekPc);
  return 0;
}