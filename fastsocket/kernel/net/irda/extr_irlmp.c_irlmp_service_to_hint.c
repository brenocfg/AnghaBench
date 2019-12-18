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
struct TYPE_2__ {int /*<<< orphan*/  word; void** byte; } ;
typedef  TYPE_1__ __u16_host_order ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 void*** service_hint_mapping ; 

__u16 irlmp_service_to_hint(int service)
{
	__u16_host_order hint;

	hint.byte[0] = service_hint_mapping[service][0];
	hint.byte[1] = service_hint_mapping[service][1];

	return hint.word;
}