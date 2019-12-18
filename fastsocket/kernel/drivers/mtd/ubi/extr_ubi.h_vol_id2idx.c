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
struct ubi_device {int vtbl_slots; } ;

/* Variables and functions */
 int UBI_INTERNAL_VOL_START ; 

__attribute__((used)) static inline int vol_id2idx(const struct ubi_device *ubi, int vol_id)
{
	if (vol_id >= UBI_INTERNAL_VOL_START)
		return vol_id - UBI_INTERNAL_VOL_START + ubi->vtbl_slots;
	else
		return vol_id;
}