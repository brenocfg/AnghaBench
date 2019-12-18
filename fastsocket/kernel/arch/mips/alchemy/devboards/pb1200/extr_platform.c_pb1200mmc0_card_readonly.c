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
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int BCSR_STATUS_SD0WP ; 
 TYPE_1__* bcsr ; 

__attribute__((used)) static int pb1200mmc0_card_readonly(void *mmc_host)
{
	return (bcsr->status & BCSR_STATUS_SD0WP) ? 1 : 0;
}