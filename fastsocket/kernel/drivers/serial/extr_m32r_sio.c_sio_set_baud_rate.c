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
struct TYPE_2__ {unsigned long bus_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M32R_SIO0_BAUR_PORTL ; 
 int /*<<< orphan*/  M32R_SIO0_RBAUR_PORTL ; 
 int /*<<< orphan*/  __sio_out (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static inline void sio_set_baud_rate(unsigned long baud)
{
	unsigned long i, j;

	i = boot_cpu_data.bus_clock / (baud * 16);
	j = (boot_cpu_data.bus_clock - (i * baud * 16)) / baud;
	i -= 1;
	j = (j + 1) >> 1;

	__sio_out(i, M32R_SIO0_BAUR_PORTL);
	__sio_out(j, M32R_SIO0_RBAUR_PORTL);
}