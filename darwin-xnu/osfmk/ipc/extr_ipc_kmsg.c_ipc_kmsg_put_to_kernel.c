#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  TYPE_1__* ipc_kmsg_t ;
struct TYPE_4__ {scalar_t__ ikm_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_kmsg_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 

void
ipc_kmsg_put_to_kernel(
	mach_msg_header_t	*msg,
	ipc_kmsg_t		kmsg,
	mach_msg_size_t		size)
{
	(void) memcpy((void *) msg, (const void *) kmsg->ikm_header, size);

	ipc_kmsg_free(kmsg);
}