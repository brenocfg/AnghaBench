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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_5__ {unsigned short Length; scalar_t__ Address; } ;
struct TYPE_4__ {int Length; int /*<<< orphan*/  Opcode; } ;
struct TYPE_6__ {TYPE_2__ FWLoadFinish; TYPE_1__ hdr; } ;
struct ngene_command {int in_len; scalar_t__ out_len; TYPE_3__ cmd; } ;
struct ngene {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FWLOAD_FINISH ; 
 int /*<<< orphan*/  CMD_FWLOAD_PREPARE ; 
 scalar_t__ DATA_FIFO_AREA ; 
 int FIRSTCHUNK ; 
 scalar_t__ PROGRAM_SRAM ; 
 int /*<<< orphan*/  memset (struct ngene_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngcpyto (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int ngene_command (struct ngene*,struct ngene_command*) ; 

__attribute__((used)) static int ngene_command_load_firmware(struct ngene *dev,
				       u8 *ngene_fw, u32 size)
{
#define FIRSTCHUNK (1024)
	u32 cleft;
	struct ngene_command com;

	com.cmd.hdr.Opcode = CMD_FWLOAD_PREPARE;
	com.cmd.hdr.Length = 0;
	com.in_len = 0;
	com.out_len = 0;

	ngene_command(dev, &com);

	cleft = (size + 3) & ~3;
	if (cleft > FIRSTCHUNK) {
		ngcpyto(PROGRAM_SRAM + FIRSTCHUNK, ngene_fw + FIRSTCHUNK,
			cleft - FIRSTCHUNK);
		cleft = FIRSTCHUNK;
	}
	ngcpyto(DATA_FIFO_AREA, ngene_fw, cleft);

	memset(&com, 0, sizeof(struct ngene_command));
	com.cmd.hdr.Opcode = CMD_FWLOAD_FINISH;
	com.cmd.hdr.Length = 4;
	com.cmd.FWLoadFinish.Address = DATA_FIFO_AREA;
	com.cmd.FWLoadFinish.Length = (unsigned short)cleft;
	com.in_len = 4;
	com.out_len = 0;

	return ngene_command(dev, &com);
}