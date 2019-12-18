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
struct nbio_linux_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCB_CMD_PWRITE ; 
 int /*<<< orphan*/  nbio_begin_op (struct nbio_linux_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbio_linux_begin_write(void *data)
{
   struct nbio_linux_t* handle = (struct nbio_linux_t*)data;
   if (handle)
      nbio_begin_op(handle, IOCB_CMD_PWRITE);
}