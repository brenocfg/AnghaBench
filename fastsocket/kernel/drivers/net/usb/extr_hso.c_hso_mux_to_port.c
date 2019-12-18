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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HSO_PORT_APP ; 
 int /*<<< orphan*/  HSO_PORT_APP2 ; 
 int /*<<< orphan*/  HSO_PORT_CONTROL ; 
 int /*<<< orphan*/  HSO_PORT_GPS ; 
 int /*<<< orphan*/  HSO_PORT_NO_PORT ; 
 int /*<<< orphan*/  HSO_PORT_PCSC ; 

__attribute__((used)) static u32 hso_mux_to_port(int mux)
{
	u32 result;

	switch (mux) {
	case 0x1:
		result = HSO_PORT_CONTROL;
		break;
	case 0x2:
		result = HSO_PORT_APP;
		break;
	case 0x4:
		result = HSO_PORT_PCSC;
		break;
	case 0x8:
		result = HSO_PORT_GPS;
		break;
	case 0x10:
		result = HSO_PORT_APP2;
		break;
	default:
		result = HSO_PORT_NO_PORT;
	}
	return result;
}