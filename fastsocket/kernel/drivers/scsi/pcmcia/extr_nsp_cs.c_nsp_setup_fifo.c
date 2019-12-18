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
struct TYPE_3__ {unsigned int BaseAddress; unsigned char TransferMode; } ;
typedef  TYPE_1__ nsp_hw_data ;

/* Variables and functions */
 unsigned char BRAIND ; 
 int FALSE ; 
 int /*<<< orphan*/  TRANSFERMODE ; 
 unsigned char TRANSFER_GO ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void nsp_setup_fifo(nsp_hw_data *data, int enabled)
{
	unsigned int  base = data->BaseAddress;
	unsigned char transfer_mode_reg;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "enabled=%d", enabled);

	if (enabled != FALSE) {
		transfer_mode_reg = TRANSFER_GO | BRAIND;
	} else {
		transfer_mode_reg = 0;
	}

	transfer_mode_reg |= data->TransferMode;

	nsp_index_write(base, TRANSFERMODE, transfer_mode_reg);
}