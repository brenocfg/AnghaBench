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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int dummy; } ;

/* Variables and functions */
 size_t MHFMAX ; 
 int /*<<< orphan*/  M_HOST_FLAGS1 ; 
 int /*<<< orphan*/  M_HOST_FLAGS2 ; 
 int /*<<< orphan*/  M_HOST_FLAGS3 ; 
 int /*<<< orphan*/  M_HOST_FLAGS4 ; 
 int /*<<< orphan*/  M_HOST_FLAGS5 ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_write_mhf(struct brcms_hardware *wlc_hw, u16 *mhfs)
{
	u8 idx;
	u16 addr[] = {
		M_HOST_FLAGS1, M_HOST_FLAGS2, M_HOST_FLAGS3, M_HOST_FLAGS4,
		M_HOST_FLAGS5
	};

	for (idx = 0; idx < MHFMAX; idx++)
		brcms_b_write_shm(wlc_hw, addr[idx], mhfs[idx]);
}