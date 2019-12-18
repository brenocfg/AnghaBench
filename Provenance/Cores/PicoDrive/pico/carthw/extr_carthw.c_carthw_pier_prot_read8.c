#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int* rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_STATUS ; 
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  carthw_pier_statef () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ pier_dump_prot ; 

__attribute__((used)) static u32 carthw_pier_prot_read8(u32 a)
{
  /* it takes more than just these reads here to disable ROM protection,
   * but for game emulation purposes this is enough. */
  if (pier_dump_prot > 0)
    pier_dump_prot--;
  if (pier_dump_prot == 0) {
    carthw_pier_statef();
    elprintf(EL_STATUS, "prot off on r8 @%06x", SekPc);
  }
  elprintf(EL_UIO, "pier r8  [%06x] @%06x", a, SekPc);

  return Pico.rom[(a & 0x7fff) ^ 1];
}