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
struct aiocb {int /*<<< orphan*/  aio_lio_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_READ ; 
 int new_req (struct aiocb*) ; 

int aio_read(struct aiocb *cb)
{
	cb->aio_lio_opcode = LIO_READ;
	return new_req(cb);
}