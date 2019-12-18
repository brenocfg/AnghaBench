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
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int /*<<< orphan*/  elprintf (int,char*,int,int,int /*<<< orphan*/ ) ; 
 int rST ; 

__attribute__((used)) static void write_ST(u32 d)
{
  /* if ((rST ^ d) & 0x0007) elprintf(EL_SVP, "ssp RPL %i -> %i @ %04x", rST&7, d&7, GET_PPC_OFFS()); */
#ifdef LOG_SVP
  if ((rST ^ d) & 0x0f98) elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME ST %04x -> %04x @ %04x", rST, d, GET_PPC_OFFS());
#endif
  rST = d;
}