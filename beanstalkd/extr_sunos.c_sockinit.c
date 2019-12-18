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

/* Variables and functions */
 int port_create () ; 
 int portfd ; 
 int /*<<< orphan*/  twarn (char*) ; 

int
sockinit(void)
{
    portfd = port_create();
    if (portfd == -1) {
        twarn("port_create");
        return -1;
    }
    return 0;
}