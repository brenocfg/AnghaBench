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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  __aio_close (int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __stdio_close(FILE *f)
{
	return syscall(SYS_close, __aio_close(f->fd));
}