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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct fcf_record {int dummy; } ;

/* Variables and functions */
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_6 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_7 ; 

__attribute__((used)) static uint32_t
lpfc_sw_name_match(uint8_t *sw_name, struct fcf_record *new_fcf_record)
{
	if (sw_name[0] != bf_get(lpfc_fcf_record_switch_name_0, new_fcf_record))
		return 0;
	if (sw_name[1] != bf_get(lpfc_fcf_record_switch_name_1, new_fcf_record))
		return 0;
	if (sw_name[2] != bf_get(lpfc_fcf_record_switch_name_2, new_fcf_record))
		return 0;
	if (sw_name[3] != bf_get(lpfc_fcf_record_switch_name_3, new_fcf_record))
		return 0;
	if (sw_name[4] != bf_get(lpfc_fcf_record_switch_name_4, new_fcf_record))
		return 0;
	if (sw_name[5] != bf_get(lpfc_fcf_record_switch_name_5, new_fcf_record))
		return 0;
	if (sw_name[6] != bf_get(lpfc_fcf_record_switch_name_6, new_fcf_record))
		return 0;
	if (sw_name[7] != bf_get(lpfc_fcf_record_switch_name_7, new_fcf_record))
		return 0;
	return 1;
}