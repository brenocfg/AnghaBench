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
struct hvcs_struct {int /*<<< orphan*/ * p_location_code; int /*<<< orphan*/  p_partition_ID; int /*<<< orphan*/  p_unit_address; } ;
struct hvcs_partner_info {int /*<<< orphan*/ * location_code; int /*<<< orphan*/  partition_ID; int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int HVCS_CLC_LENGTH ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hvcs_set_pi(struct hvcs_partner_info *pi, struct hvcs_struct *hvcsd)
{
	int clclength;

	hvcsd->p_unit_address = pi->unit_address;
	hvcsd->p_partition_ID  = pi->partition_ID;
	clclength = strlen(&pi->location_code[0]);
	if (clclength > HVCS_CLC_LENGTH)
		clclength = HVCS_CLC_LENGTH;

	/* copy the null-term char too */
	strncpy(&hvcsd->p_location_code[0],
			&pi->location_code[0], clclength + 1);
}