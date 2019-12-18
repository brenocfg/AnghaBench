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
struct aio_context {int dummy; } ;
typedef  enum aio_type { ____Placeholder_aio_type } aio_type ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int submit_aio_26(enum aio_type type, int io_fd, char *buf, int len,
			 unsigned long long offset, struct aio_context *aio)
{
	return -ENOSYS;
}