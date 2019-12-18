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
struct TYPE_2__ {int w; int adrmode0; int opsz; int status; int /*<<< orphan*/  ea; int /*<<< orphan*/  branch; int /*<<< orphan*/  szchar; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 int DESA68_BRA ; 
 int DESA68_BSR ; 
 int DESA68_INST ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (int) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_dcw () ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_desa_jmp()
{
  int modemsk = 03744;
  if((d.w&07600) != 07200) {
    return 0;
  }
  /* JMP / JSR */
  if(modemsk & (1<<d.adrmode0)) {
    int s = 'MP ', stat = DESA68_INST | DESA68_BRA;
    desa_char('J');
    if (d.opsz==2) {
      stat = DESA68_INST | DESA68_BRA | DESA68_BSR;
      s = 'SR ';
    }
    d.status = stat;
    desa_ascii(s);
    get_ea_2(d.mode3, d.reg0, d.szchar);
    d.branch = d.ea;

    return 1;
  }
  /* invalid JSR / JMP address mode */
  /* $$$ Not sure for a DC.W here */
  desa_dcw();
  return 1;
  /*return 0;*/
}