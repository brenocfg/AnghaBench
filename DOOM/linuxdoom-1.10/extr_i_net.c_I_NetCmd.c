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
struct TYPE_2__ {scalar_t__ command; } ;

/* Variables and functions */
 scalar_t__ CMD_GET ; 
 scalar_t__ CMD_SEND ; 
 int /*<<< orphan*/  I_Error (char*,scalar_t__) ; 
 TYPE_1__* doomcom ; 
 int /*<<< orphan*/  netget () ; 
 int /*<<< orphan*/  netsend () ; 

void I_NetCmd (void)
{
    if (doomcom->command == CMD_SEND)
    {
	netsend ();
    }
    else if (doomcom->command == CMD_GET)
    {
	netget ();
    }
    else
	I_Error ("Bad net cmd: %i\n",doomcom->command);
}