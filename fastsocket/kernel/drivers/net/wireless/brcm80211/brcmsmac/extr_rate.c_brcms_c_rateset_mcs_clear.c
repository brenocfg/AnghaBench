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
typedef  size_t uint ;
struct brcms_c_rateset {scalar_t__* mcs; } ;

/* Variables and functions */
 size_t MCSSET_LEN ; 

void brcms_c_rateset_mcs_clear(struct brcms_c_rateset *rateset)
{
	uint i;
	for (i = 0; i < MCSSET_LEN; i++)
		rateset->mcs[i] = 0;
}