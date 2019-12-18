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
struct timespec {int dummy; } ;
struct io_event {int dummy; } ;
typedef  int /*<<< orphan*/  aio_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_io_getevents ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,struct io_event*,struct timespec*) ; 

__attribute__((used)) static int io_getevents(aio_context_t ctx, long min_nr, long nr,
      struct io_event * events, struct timespec * timeout)
{
   return syscall(__NR_io_getevents, ctx, min_nr, nr, events, timeout);
}