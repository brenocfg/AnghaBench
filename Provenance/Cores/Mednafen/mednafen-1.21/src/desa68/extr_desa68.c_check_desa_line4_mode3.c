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
struct TYPE_2__ {int mode6; int reg9; int adrmode0; int w; int status; int branch; int /*<<< orphan*/  szchar; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 int DESA68_INST ; 
 int DESA68_INT ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_check_imp (char,int) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int check_desa_line4_mode3(void)
{
  if (d.mode6 != 3) {
    return 0;
  }

  switch(d.reg9)
    {

    case 0:				/* MOVE FROM SR */
      {
	int modemsk = 00775;
	if(!(modemsk&(1<<d.adrmode0)))
	  break;
	desa_ascii('MOVE');
	desa_ascii(' SR,');
	get_ea_2(d.mode3, d.reg0, 'W');
	return 1;
      }

    case 1:
      break;

    case 2:			/* MOVE TO CCR */
      {
	int modemsk = 07775;
	if(!(modemsk&(1<<d.adrmode0)))
	  break;
	desa_ascii('MOVE');
	desa_char (' ');
	get_ea_2(d.mode3, d.reg0, 'B');
	desa_ascii(',CCR');
	return 1;
      }

    case 3:			/* MOVE TO SR */
      {
	int modemsk = 07775;
	if(!(modemsk&(1<<d.adrmode0)))
	  break;
	desa_ascii('MOVE');
	desa_char (' ');
	get_ea_2(d.mode3, d.reg0, 'W');
	desa_ascii(',SR');
	return 1;
      }

    case 4:
      break;

    case 5:			/* TAS */
      {
	d.szchar = 0;
	if(desa_check_imp('TAS', 00775)) {
	  return 1;
	} else if(d.w == 0x4AFC) {
	  desa_ascii('ILLE');
	  desa_ascii('GAL');
	  d.status = DESA68_INST | DESA68_INT;
	  d.branch = 0x10;
	  return 1;
	}
      }
      break;

    case 6:
      break;

    case 7:
      break;
    }
  return 0;
}