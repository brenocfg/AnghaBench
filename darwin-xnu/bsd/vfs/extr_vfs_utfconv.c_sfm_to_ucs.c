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
typedef  int u_int16_t ;

/* Variables and functions */
 int MAX_SFM2MAC ; 
 int SFM2MAC_LEN ; 
 int SFMCODE_PREFIX_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int* sfm2mac ; 

__attribute__((used)) static u_int16_t
sfm_to_ucs(u_int16_t ucs_ch)
{
	if (((ucs_ch & 0xffC0) == SFMCODE_PREFIX_MASK) && 
	    ((ucs_ch & 0x003f) <= MAX_SFM2MAC)) {
		assert((ucs_ch & 0x003f) < SFM2MAC_LEN);
		ucs_ch = sfm2mac[ucs_ch & 0x003f];
	}
	return (ucs_ch);
}