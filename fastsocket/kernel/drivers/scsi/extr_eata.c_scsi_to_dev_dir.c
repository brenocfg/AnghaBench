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
struct scsi_cmnd {scalar_t__ sc_data_direction; unsigned char const* cmnd; } ;
struct mscp {int din; int dout; struct scsi_cmnd* SCpnt; } ;
struct hostdata {int /*<<< orphan*/  board_name; struct mscp* cp; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned char const*) ; 
 scalar_t__ DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_to_dev_dir(unsigned int i, struct hostdata *ha)
{
	unsigned int k;

	static const unsigned char data_out_cmds[] = {
		0x0a, 0x2a, 0x15, 0x55, 0x04, 0x07, 0x18, 0x1d, 0x24, 0x2e,
		0x30, 0x31, 0x32, 0x38, 0x39, 0x3a, 0x3b, 0x3d, 0x3f, 0x40,
		0x41, 0x4c, 0xaa, 0xae, 0xb0, 0xb1, 0xb2, 0xb6, 0xea, 0x1b, 0x5d
	};

	static const unsigned char data_none_cmds[] = {
		0x01, 0x0b, 0x10, 0x11, 0x13, 0x16, 0x17, 0x19, 0x2b, 0x1e,
		0x2c, 0xac, 0x2f, 0xaf, 0x33, 0xb3, 0x35, 0x36, 0x45, 0x47,
		0x48, 0x49, 0xa9, 0x4b, 0xa5, 0xa6, 0xb5, 0x00
	};

	struct mscp *cpp;
	struct scsi_cmnd *SCpnt;

	cpp = &ha->cp[i];
	SCpnt = cpp->SCpnt;

	if (SCpnt->sc_data_direction == DMA_FROM_DEVICE) {
		cpp->din = 1;
		cpp->dout = 0;
		return;
	} else if (SCpnt->sc_data_direction == DMA_TO_DEVICE) {
		cpp->din = 0;
		cpp->dout = 1;
		return;
	} else if (SCpnt->sc_data_direction == DMA_NONE) {
		cpp->din = 0;
		cpp->dout = 0;
		return;
	}

	if (SCpnt->sc_data_direction != DMA_BIDIRECTIONAL)
		panic("%s: qcomm, invalid SCpnt->sc_data_direction.\n",
				ha->board_name);

	for (k = 0; k < ARRAY_SIZE(data_out_cmds); k++)
		if (SCpnt->cmnd[0] == data_out_cmds[k]) {
			cpp->dout = 1;
			break;
		}

	if ((cpp->din = !cpp->dout))
		for (k = 0; k < ARRAY_SIZE(data_none_cmds); k++)
			if (SCpnt->cmnd[0] == data_none_cmds[k]) {
				cpp->din = 0;
				break;
			}

}