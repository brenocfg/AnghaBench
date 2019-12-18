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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int im; int entry_latency; int exit_latency; int power_consumption; scalar_t__ co; } ;
struct TYPE_5__ {TYPE_1__ pal_power_mgmt_info_s; } ;
typedef  TYPE_2__ pal_power_mgmt_info_u_t ;

/* Variables and functions */
 scalar_t__ ia64_pal_halt_info (TYPE_2__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static int
power_info(char *page)
{
	s64 status;
	char *p = page;
	u64 halt_info_buffer[8];
	pal_power_mgmt_info_u_t *halt_info =(pal_power_mgmt_info_u_t *)halt_info_buffer;
	int i;

	status = ia64_pal_halt_info(halt_info);
	if (status != 0) return 0;

	for (i=0; i < 8 ; i++ ) {
		if (halt_info[i].pal_power_mgmt_info_s.im == 1) {
			p += sprintf(p,	"Power level %d:\n"
				     "\tentry_latency       : %d cycles\n"
				     "\texit_latency        : %d cycles\n"
				     "\tpower consumption   : %d mW\n"
				     "\tCache+TLB coherency : %s\n", i,
				     halt_info[i].pal_power_mgmt_info_s.entry_latency,
				     halt_info[i].pal_power_mgmt_info_s.exit_latency,
				     halt_info[i].pal_power_mgmt_info_s.power_consumption,
				     halt_info[i].pal_power_mgmt_info_s.co ? "Yes" : "No");
		} else {
			p += sprintf(p,"Power level %d: not implemented\n",i);
		}
	}
	return p - page;
}