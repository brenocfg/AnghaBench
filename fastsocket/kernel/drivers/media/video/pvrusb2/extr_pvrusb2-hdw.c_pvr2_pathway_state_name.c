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
#define  PVR2_PATHWAY_ANALOG 129 
#define  PVR2_PATHWAY_DIGITAL 128 

__attribute__((used)) static const char *pvr2_pathway_state_name(int id)
{
	switch (id) {
	case PVR2_PATHWAY_ANALOG: return "analog";
	case PVR2_PATHWAY_DIGITAL: return "digital";
	default: return "unknown";
	}
}