#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_t ;
struct TYPE_2__ {int version; void (* pthread_clear_qos_tsd ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_functions ; 
 void stub1 (int /*<<< orphan*/ ) ; 

__attribute__((visibility("hidden")))
void
_pthread_clear_qos_tsd(mach_port_t thread_port)
{
	if (_libkernel_functions->version >= 3 &&
			_libkernel_functions->pthread_clear_qos_tsd) {
		return _libkernel_functions->pthread_clear_qos_tsd(thread_port);
	}
}