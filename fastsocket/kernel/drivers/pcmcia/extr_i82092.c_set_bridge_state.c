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
 int /*<<< orphan*/  I365_GBLCTL ; 
 int /*<<< orphan*/  I365_GENCTL ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 int /*<<< orphan*/  enter (char*) ; 
 int /*<<< orphan*/  indirect_setbit (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  indirect_write (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  leave (char*) ; 

__attribute__((used)) static void set_bridge_state(int sock)
{
	enter("set_bridge_state");
	indirect_write(sock, I365_GBLCTL,0x00);
	indirect_write(sock, I365_GENCTL,0x00);
	
	indirect_setbit(sock, I365_INTCTL,0x08);
	leave("set_bridge_state");
}