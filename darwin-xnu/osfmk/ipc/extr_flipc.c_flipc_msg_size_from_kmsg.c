#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_size_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_5__ {TYPE_1__* ikm_header; } ;
struct TYPE_4__ {int msgh_bits; int /*<<< orphan*/  msgh_size; } ;

/* Variables and functions */
 int MACH_MSGH_BITS_COMPLEX ; 
 int /*<<< orphan*/  PE_enter_debugger (char*) ; 

__attribute__((used)) static mach_msg_size_t flipc_msg_size_from_kmsg(ipc_kmsg_t kmsg)
{
    mach_msg_size_t fsize = kmsg->ikm_header->msgh_size;

    if (kmsg->ikm_header->msgh_bits & MACH_MSGH_BITS_COMPLEX)
        PE_enter_debugger("flipc_msg_size_from_kmsg(): Complex messages not supported.");

    return fsize;
}