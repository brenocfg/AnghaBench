#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_pointer {scalar_t__ this_residual; } ;
typedef  scalar_t__ fasdmadir_t ;
struct TYPE_7__ {struct scsi_pointer SCp; } ;
struct TYPE_8__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 scalar_t__ DMA_OUT ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_2__*) ; 
 int /*<<< orphan*/  fas216_readb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_next_SCp_byte (struct scsi_pointer*) ; 
 int /*<<< orphan*/  next_SCp (struct scsi_pointer*) ; 
 int /*<<< orphan*/  put_next_SCp_byte (struct scsi_pointer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fas216_pio(FAS216_Info *info, fasdmadir_t direction)
{
	struct scsi_pointer *SCp = &info->scsi.SCp;

	fas216_checkmagic(info);

	if (direction == DMA_OUT)
		fas216_writeb(info, REG_FF, get_next_SCp_byte(SCp));
	else
		put_next_SCp_byte(SCp, fas216_readb(info, REG_FF));

	if (SCp->this_residual == 0)
		next_SCp(SCp);
}