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
struct iocb {int dummy; } ;
struct io_event {int dummy; } ;
typedef  int /*<<< orphan*/  aio_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_io_cancel ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iocb*,struct io_event*) ; 

__attribute__((used)) static int io_cancel(aio_context_t ctx, struct iocb * iocb, struct io_event * result)
{
   return syscall(__NR_io_cancel, ctx, iocb, result);
}