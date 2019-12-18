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
struct ubi_device {int beb_rsvd_level; int good_peb_count; } ;

/* Variables and functions */
 int CONFIG_MTD_UBI_BEB_RESERVE ; 
 int MIN_RESEVED_PEBS ; 

void ubi_calculate_reserved(struct ubi_device *ubi)
{
	ubi->beb_rsvd_level = ubi->good_peb_count/100;
	ubi->beb_rsvd_level *= CONFIG_MTD_UBI_BEB_RESERVE;
	if (ubi->beb_rsvd_level < MIN_RESEVED_PEBS)
		ubi->beb_rsvd_level = MIN_RESEVED_PEBS;
}