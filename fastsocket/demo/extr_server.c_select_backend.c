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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  param_port; int /*<<< orphan*/  param_ip; int /*<<< orphan*/  proxyip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* pa ; 
 int pa_num ; 
 int /*<<< orphan*/  print_d (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void select_backend(struct sockaddr_in *addr)
{
	static int last;

	addr->sin_family = AF_INET;
	addr->sin_port = htons(pa[last].param_port);
	addr->sin_addr = pa[last].proxyip;

	print_d("Select Back-end server %s:%d\n", pa[last].param_ip,
		pa[last].param_port);

	last++;

	if (last == pa_num)
		last = 0;
}