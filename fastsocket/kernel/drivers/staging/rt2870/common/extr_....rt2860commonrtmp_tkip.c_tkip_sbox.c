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
typedef  int UINT ;

/* Variables and functions */
 int* Tkip_Sbox_Lower ; 
 int* Tkip_Sbox_Upper ; 

UINT tkip_sbox(UINT index)
{
	UINT index_low;
	UINT index_high;
	UINT left, right;

	index_low = (index % 256);
	index_high = ((index >> 8) % 256);

	left = Tkip_Sbox_Lower[index_low] + (Tkip_Sbox_Upper[index_low] * 256);
	right = Tkip_Sbox_Upper[index_high] + (Tkip_Sbox_Lower[index_high] * 256);

	return (left ^ right);
}