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
typedef  int u32 ;
typedef  enum stv090x_rolloff { ____Placeholder_stv090x_rolloff } stv090x_rolloff ;

/* Variables and functions */
#define  STV090x_RO_20 130 
#define  STV090x_RO_25 129 
#define  STV090x_RO_35 128 

__attribute__((used)) static u32 stv090x_car_width(u32 srate, enum stv090x_rolloff rolloff)
{
	u32 ro;

	switch (rolloff) {
	case STV090x_RO_20:
		ro = 20;
		break;
	case STV090x_RO_25:
		ro = 25;
		break;
	case STV090x_RO_35:
	default:
		ro = 35;
		break;
	}

	return srate + (srate * ro) / 100;
}