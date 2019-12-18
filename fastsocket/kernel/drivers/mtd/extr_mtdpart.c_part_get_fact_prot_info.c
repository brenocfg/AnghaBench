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
struct otp_info {int dummy; } ;
struct mtd_part {TYPE_1__* master; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int (* get_fact_prot_info ) (TYPE_1__*,struct otp_info*,size_t) ;} ;

/* Variables and functions */
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,struct otp_info*,size_t) ; 

__attribute__((used)) static int part_get_fact_prot_info(struct mtd_info *mtd, struct otp_info *buf,
		size_t len)
{
	struct mtd_part *part = PART(mtd);
	return part->master->get_fact_prot_info(part->master, buf, len);
}