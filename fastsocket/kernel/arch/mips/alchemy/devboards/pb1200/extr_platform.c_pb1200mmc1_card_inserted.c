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
struct TYPE_2__ {int sig_status; } ;

/* Variables and functions */
 int BCSR_INT_SD1INSERT ; 
 TYPE_1__* bcsr ; 

__attribute__((used)) static int pb1200mmc1_card_inserted(void *mmc_host)
{
	return (bcsr->sig_status & BCSR_INT_SD1INSERT) ? 1 : 0;
}