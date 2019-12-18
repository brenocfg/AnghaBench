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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ PA_MRSHPC ; 
 scalar_t__ PA_SMSC ; 

__attribute__((used)) static inline volatile __u16 *
port2adr(unsigned int port)
{
	if (port >= 0x2000 && port < 0x2020)
		return (volatile __u16 *) (PA_MRSHPC + (port - 0x2000));
	else if (port >= 0x300 && port < 0x310)
		return (volatile __u16 *) (PA_SMSC + (port - 0x300));

	return (volatile __u16 *)port;
}