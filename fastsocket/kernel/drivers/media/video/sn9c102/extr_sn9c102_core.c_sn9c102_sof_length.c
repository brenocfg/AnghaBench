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
struct sn9c102_device {int bridge; } ;

/* Variables and functions */
#define  BRIDGE_SN9C101 132 
#define  BRIDGE_SN9C102 131 
#define  BRIDGE_SN9C103 130 
#define  BRIDGE_SN9C105 129 
#define  BRIDGE_SN9C120 128 

__attribute__((used)) static size_t sn9c102_sof_length(struct sn9c102_device* cam)
{
	switch (cam->bridge) {
	case BRIDGE_SN9C101:
	case BRIDGE_SN9C102:
		return 12;
	case BRIDGE_SN9C103:
		return 18;
	case BRIDGE_SN9C105:
	case BRIDGE_SN9C120:
		return 62;
	}

	return 0;
}