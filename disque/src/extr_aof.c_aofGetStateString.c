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
struct TYPE_2__ {int aof_state; } ;

/* Variables and functions */
#define  AOF_OFF 130 
#define  AOF_ON 129 
#define  AOF_WAIT_REWRITE 128 
 TYPE_1__ server ; 

char *aofGetStateString(void) {
    switch(server.aof_state) {
    case AOF_OFF: return "off";
    case AOF_ON: return "on";
    case AOF_WAIT_REWRITE: return "wait-rewrite";
    default: return "unknown";
    }
}