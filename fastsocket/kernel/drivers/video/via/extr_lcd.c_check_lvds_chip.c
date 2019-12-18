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

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int lvds_register_read (int) ; 

__attribute__((used)) static int check_lvds_chip(int device_id_subaddr, int device_id)
{
	if (lvds_register_read(device_id_subaddr) == device_id)
		return OK;
	else
		return FAIL;
}