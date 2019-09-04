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
typedef  double uint64_t ;
struct TYPE_2__ {scalar_t__ numer; scalar_t__ denom; } ;

/* Variables and functions */
 TYPE_1__ g_mti ; 

__attribute__((used)) static uint64_t
nanos_to_abs(uint64_t ns)
{
	return (uint64_t)(ns * (((double)g_mti.denom) / ((double)g_mti.numer)));
}