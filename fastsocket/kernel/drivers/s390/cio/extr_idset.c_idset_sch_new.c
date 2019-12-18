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
struct idset {int dummy; } ;

/* Variables and functions */
 scalar_t__ __MAX_SUBCHANNEL ; 
 struct idset* idset_new (scalar_t__,scalar_t__) ; 
 scalar_t__ max_ssid ; 

struct idset *idset_sch_new(void)
{
	return idset_new(max_ssid + 1, __MAX_SUBCHANNEL + 1);
}