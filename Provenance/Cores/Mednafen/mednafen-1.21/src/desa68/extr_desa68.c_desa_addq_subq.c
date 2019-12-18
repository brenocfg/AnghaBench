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
struct TYPE_2__ {int reg9; int w; char szchar; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void desa_addq_subq()
{
  int v;
  v = d.reg9 * 256;
  if(v==0) v=8*256;
  desa_ascii((d.w&0400) ? 'SUBQ':'ADDQ');
  desa_ascii(d.szchar);
  desa_ascii(' #0,' + v);
  get_ea_2(d.mode3, d.reg0, d.szchar);
}