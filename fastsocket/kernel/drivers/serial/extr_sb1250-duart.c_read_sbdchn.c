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
struct sbd_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIBYTE_1956_WAR ; 
 unsigned char __read_sbdchn (struct sbd_port*,int) ; 
 int /*<<< orphan*/  __war_sbd1956 (struct sbd_port*) ; 

__attribute__((used)) static unsigned char read_sbdchn(struct sbd_port *sport, int reg)
{
	unsigned char retval;

	retval = __read_sbdchn(sport, reg);
	if (SIBYTE_1956_WAR)
		__war_sbd1956(sport);
	return retval;
}