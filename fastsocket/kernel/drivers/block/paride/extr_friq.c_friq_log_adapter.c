#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t device; size_t mode; int private; int /*<<< orphan*/  delay; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 char* FRIQ_VERSION ; 
 int /*<<< orphan*/  friq_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  friq_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void friq_log_adapter( PIA *pi, char * scratch, int verbose )

{       char    *mode_string[6] = {"4-bit","8-bit",
				   "EPP-8","EPP-16","EPP-32"};

        printk("%s: friq %s, Freecom IQ ASIC-2 adapter at 0x%x, ", pi->device,
		FRIQ_VERSION,pi->port);
        printk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

	pi->private = 1;
	friq_connect(pi);
	CMD(0x9e);  		/* disable sleep timer */
	friq_disconnect(pi);

}