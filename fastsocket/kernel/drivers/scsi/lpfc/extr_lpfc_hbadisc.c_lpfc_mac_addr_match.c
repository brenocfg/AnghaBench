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
 int /*<<< orphan*/  lpfc_fcf_record_mac_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_5 ; 

__attribute__((used)) static uint32_t
lpfc_mac_addr_match(uint8_t *mac_addr, struct fcf_record *new_fcf_record)
{
	if (mac_addr[0] != bf_get(lpfc_fcf_record_mac_0, new_fcf_record))
		return 0;
	if (mac_addr[1] != bf_get(lpfc_fcf_record_mac_1, new_fcf_record))
		return 0;
	if (mac_addr[2] != bf_get(lpfc_fcf_record_mac_2, new_fcf_record))
		return 0;
	if (mac_addr[3] != bf_get(lpfc_fcf_record_mac_3, new_fcf_record))
		return 0;
	if (mac_addr[4] != bf_get(lpfc_fcf_record_mac_4, new_fcf_record))
		return 0;
	if (mac_addr[5] != bf_get(lpfc_fcf_record_mac_5, new_fcf_record))
		return 0;
	return 1;
}