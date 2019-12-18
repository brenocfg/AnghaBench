#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct cpm_bd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tbase; int /*<<< orphan*/  rbase; int /*<<< orphan*/  brkcr; int /*<<< orphan*/  brkln; int /*<<< orphan*/  brkec; int /*<<< orphan*/  maxidl; int /*<<< orphan*/  mrblr; int /*<<< orphan*/  tfcr; int /*<<< orphan*/  rfcr; } ;
struct TYPE_5__ {int sc; int len; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPM_CMD_INIT_RX_TX ; 
 TYPE_1__* cbd_addr ; 
 int cbd_offset ; 
 int /*<<< orphan*/  disable_port () ; 
 int /*<<< orphan*/  do_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_port () ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* param ; 
 TYPE_1__* rbdf ; 
 int /*<<< orphan*/  sync () ; 
 TYPE_1__* tbdf ; 

__attribute__((used)) static int cpm_serial_open(void)
{
	disable_port();

	out_8(&param->rfcr, 0x10);
	out_8(&param->tfcr, 0x10);
	out_be16(&param->mrblr, 1);
	out_be16(&param->maxidl, 0);
	out_be16(&param->brkec, 0);
	out_be16(&param->brkln, 0);
	out_be16(&param->brkcr, 0);

	rbdf = cbd_addr;
	rbdf->addr = (u8 *)rbdf - 1;
	rbdf->sc = 0xa000;
	rbdf->len = 1;

	tbdf = rbdf + 1;
	tbdf->addr = (u8 *)rbdf - 2;
	tbdf->sc = 0x2000;
	tbdf->len = 1;

	sync();
	out_be16(&param->rbase, cbd_offset);
	out_be16(&param->tbase, cbd_offset + sizeof(struct cpm_bd));

	do_cmd(CPM_CMD_INIT_RX_TX);

	enable_port();
	return 0;
}