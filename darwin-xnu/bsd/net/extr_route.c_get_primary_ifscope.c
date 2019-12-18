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
 int AF_INET ; 
 unsigned int primary6_ifscope ; 
 unsigned int primary_ifscope ; 

unsigned int
get_primary_ifscope(int af)
{
	return (af == AF_INET ? primary_ifscope : primary6_ifscope);
}