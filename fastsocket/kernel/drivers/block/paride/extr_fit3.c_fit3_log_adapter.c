#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t mode; int /*<<< orphan*/  delay; int /*<<< orphan*/  port; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  FIT3_VERSION ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fit3_log_adapter( PIA *pi, char * scratch, int verbose )

{       char    *mode_string[3] = {"4-bit","8-bit","EPP"};

	printk("%s: fit3 %s, FIT 3000 adapter at 0x%x, "
	       "mode %d (%s), delay %d\n",
                pi->device,FIT3_VERSION,pi->port,
		pi->mode,mode_string[pi->mode],pi->delay);

}