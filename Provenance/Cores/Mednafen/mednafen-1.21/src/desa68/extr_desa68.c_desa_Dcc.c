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
struct TYPE_2__ {int w; int reg0; int status; int /*<<< orphan*/  ea; int /*<<< orphan*/  branch; scalar_t__* s; } ;

/* Variables and functions */
 int DESA68_BRA ; 
 int DESA68_BSR ; 
 int DESA68_INST ; 
 scalar_t__ MODE_ABSW ; 
 scalar_t__ MODE_dPC ; 
 TYPE_1__ d ; 
 char* dbcc_ascii ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  get_ea_2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void desa_Dcc()
{
  desa_ascii(('DB'<<16) + dbcc_ascii[(d.w>>8)&15]);
  desa_ascii(' D0,' + (d.reg0<<8));
  get_ea_2(MODE_ABSW, MODE_dPC-MODE_ABSW, 0);
  /* $$$ hack : remove (PC) at the end */
  d.s[-4] = 0;
  d.branch = d.ea;
  d.status = DESA68_INST | DESA68_BRA | DESA68_BSR;
}