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
typedef  void* u8 ;
struct request {int /*<<< orphan*/  cmd; } ;
struct ide_atapi_pc {int* c; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int blk_size; scalar_t__ buffer_size; } ;
typedef  TYPE_1__ idetape_tape_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_FLAG_DMA_OK ; 
 int /*<<< orphan*/  PC_FLAG_WRITING ; 
 void* READ_6 ; 
 void* WRITE_6 ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void ide_tape_create_rw_cmd(idetape_tape_t *tape,
				   struct ide_atapi_pc *pc, struct request *rq,
				   u8 opcode)
{
	unsigned int length = blk_rq_sectors(rq) / (tape->blk_size >> 9);

	ide_init_pc(pc);
	put_unaligned(cpu_to_be32(length), (unsigned int *) &pc->c[1]);
	pc->c[1] = 1;

	if (blk_rq_bytes(rq) == tape->buffer_size)
		pc->flags |= PC_FLAG_DMA_OK;

	if (opcode == READ_6)
		pc->c[0] = READ_6;
	else if (opcode == WRITE_6) {
		pc->c[0] = WRITE_6;
		pc->flags |= PC_FLAG_WRITING;
	}

	memcpy(rq->cmd, pc->c, 12);
}