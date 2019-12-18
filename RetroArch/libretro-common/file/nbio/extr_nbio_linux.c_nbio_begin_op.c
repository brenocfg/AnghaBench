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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iocb {int /*<<< orphan*/  aio_nbytes; scalar_t__ aio_offset; scalar_t__ aio_buf; int /*<<< orphan*/  aio_lio_opcode; int /*<<< orphan*/  aio_fildes; } ;
struct nbio_linux_t {int busy; int /*<<< orphan*/  ctx; int /*<<< orphan*/  len; struct iocb cb; scalar_t__ ptr; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int io_submit (int /*<<< orphan*/ ,int,struct iocb**) ; 
 int /*<<< orphan*/  memset (struct iocb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nbio_begin_op(struct nbio_linux_t* handle, uint16_t op)
{
   struct iocb * cbp         = &handle->cb;

   memset(&handle->cb, 0, sizeof(handle->cb));

   handle->cb.aio_fildes     = handle->fd;
   handle->cb.aio_lio_opcode = op;

   handle->cb.aio_buf        = (uint64_t)(uintptr_t)handle->ptr;
   handle->cb.aio_offset     = 0;
   handle->cb.aio_nbytes     = handle->len;

   if (io_submit(handle->ctx, 1, &cbp) != 1)
      abort();

   handle->busy = true;
}