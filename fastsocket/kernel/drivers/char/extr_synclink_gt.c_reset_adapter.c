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
struct slgt_info {int port_count; scalar_t__* port_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_port (scalar_t__) ; 

__attribute__((used)) static void reset_adapter(struct slgt_info *info)
{
	int i;
	for (i=0; i < info->port_count; ++i) {
		if (info->port_array[i])
			reset_port(info->port_array[i]);
	}
}