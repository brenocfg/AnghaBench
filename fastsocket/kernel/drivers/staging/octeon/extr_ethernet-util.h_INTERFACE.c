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
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static inline int INTERFACE(int ipd_port)
{
	if (ipd_port < 32)	/* Interface 0 or 1 for RGMII,GMII,SPI, etc */
		return ipd_port >> 4;
	else if (ipd_port < 36)	/* Interface 2 for NPI */
		return 2;
	else if (ipd_port < 40)	/* Interface 3 for loopback */
		return 3;
	else if (ipd_port == 40)	/* Non existant interface for POW0 */
		return 4;
	else
		panic("Illegal ipd_port %d passed to INTERFACE\n", ipd_port);
}