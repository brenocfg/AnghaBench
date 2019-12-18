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
struct TYPE_2__ {int loopc; int waitc; int* vstarts; scalar_t__ busy; } ;

/* Variables and functions */
 int crashed_940 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* shared_ctl ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

void wait_busy_940(void)
{
	int i;
#if 0
	printf("940 busy, entering wait loop.. (cnt: %i, wc: %i, ve: ", shared_ctl->loopc, shared_ctl->waitc);
	for (i = 0; i < 8; i++)
		printf("%i ", shared_ctl->vstarts[i]);
	printf(")\n");

	for (i = 0; shared_ctl->busy; i++)
	{
		spend_cycles(1024); /* needs tuning */
	}
	printf("wait iterations: %i\n", i);
#else
	for (i = 0; shared_ctl->busy && i < 0x10000; i++)
		spend_cycles(8*1024);
	if (i < 0x10000) return;

	/* 940 crashed */
	printf("940 crashed (cnt: %i, ve: ", shared_ctl->loopc);
	for (i = 0; i < 8; i++)
		printf("%i ", shared_ctl->vstarts[i]);
	printf(")\n");
	crashed_940 = 1;
#endif
}