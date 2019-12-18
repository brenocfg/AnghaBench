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
struct comp_id {int id; scalar_t__ major; } ;
typedef  enum fwtype { ____Placeholder_fwtype } fwtype ;

/* Variables and functions */
 int FIRMWARE_TYPE_AGERE ; 
 int FIRMWARE_TYPE_INTERSIL ; 
 int FIRMWARE_TYPE_SYMBOL ; 

__attribute__((used)) static inline enum fwtype determine_firmware_type(struct comp_id *nic_id)
{
	if (nic_id->id < 0x8000)
		return FIRMWARE_TYPE_AGERE;
	else if (nic_id->id == 0x8000 && nic_id->major == 0)
		return FIRMWARE_TYPE_SYMBOL;
	else
		return FIRMWARE_TYPE_INTERSIL;
}