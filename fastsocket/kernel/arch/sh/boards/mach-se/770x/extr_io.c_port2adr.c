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
 scalar_t__ PA_83902 ; 
 scalar_t__ PA_MRSHPC ; 
 scalar_t__ PA_SUPERIO ; 

__attribute__((used)) static inline volatile __u16 *
port2adr(unsigned int port)
{
	if (port & 0xff000000)
		return ( volatile __u16 *) port;
	if (port >= 0x2000)
		return (volatile __u16 *) (PA_MRSHPC + (port - 0x2000));
	else if (port >= 0x1000)
		return (volatile __u16 *) (PA_83902 + (port << 1));
	else
		return (volatile __u16 *) (PA_SUPERIO + (port << 1));
}