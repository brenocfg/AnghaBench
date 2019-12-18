#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int mode; int /*<<< orphan*/  lpt_addr; int /*<<< orphan*/  cur_ctrl; } ;
typedef  TYPE_1__ Interface ;

/* Variables and functions */
#define  PPCMODE_BI_FW 134 
#define  PPCMODE_BI_SW 133 
#define  PPCMODE_EPP_BYTE 132 
#define  PPCMODE_EPP_DWORD 131 
#define  PPCMODE_EPP_WORD 130 
#define  PPCMODE_UNI_FW 129 
#define  PPCMODE_UNI_SW 128 
 int /*<<< orphan*/  data_stb ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppc6_wr_data_byte(Interface *ppc, u8 data)
{
	switch(ppc->mode)
	{
		case PPCMODE_UNI_SW :
		case PPCMODE_UNI_FW :
		case PPCMODE_BI_SW :
		case PPCMODE_BI_FW :
		{
			outb(data, ppc->lpt_addr);

			ppc->cur_ctrl ^= data_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			break;
		}

		case PPCMODE_EPP_BYTE :
		case PPCMODE_EPP_WORD :
		case PPCMODE_EPP_DWORD :
		{
			outb(data, ppc->lpt_addr + 4);

			break;
		}
	}
}