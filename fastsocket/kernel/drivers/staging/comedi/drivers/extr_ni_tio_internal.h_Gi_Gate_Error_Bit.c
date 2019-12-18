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
typedef  enum Gxx_Status_Bits { ____Placeholder_Gxx_Status_Bits } Gxx_Status_Bits ;

/* Variables and functions */
 int G0_Gate_Error_Bit ; 
 int G1_Gate_Error_Bit ; 

__attribute__((used)) static inline enum Gxx_Status_Bits Gi_Gate_Error_Bit(unsigned counter_index)
{
	if (counter_index % 2)
		return G1_Gate_Error_Bit;
	return G0_Gate_Error_Bit;
}