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
struct TYPE_2__ {int w; int adrmode0; int line; char reg9; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int check_desa_mul_div(void)
{
  int modemsk = 0xFFD;
  if((d.w&0300)!=0300 || !(modemsk&(1<<d.adrmode0)))
    return 0;
  desa_ascii((d.line==0xC) ? 'MUL' : 'DIV');
  desa_ascii((d.w&0x100) ? 'S ' : 'U ');
  get_ea_2  (d.mode3, d.reg0, 'W');
  desa_ascii(',D0'+d.reg9);
  return 1;
}