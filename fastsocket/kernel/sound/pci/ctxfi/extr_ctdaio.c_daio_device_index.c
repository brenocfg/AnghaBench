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
struct hw {int chip_type; } ;
typedef  enum DAIOTYP { ____Placeholder_DAIOTYP } DAIOTYP ;

/* Variables and functions */
#define  ATC20K1 137 
#define  ATC20K2 136 
 unsigned int EINVAL ; 
#define  LINEIM 135 
#define  LINEO1 134 
#define  LINEO2 133 
#define  LINEO3 132 
#define  LINEO4 131 
#define  SPDIFI1 130 
#define  SPDIFIO 129 
#define  SPDIFOO 128 

__attribute__((used)) static unsigned int daio_device_index(enum DAIOTYP type, struct hw *hw)
{
	switch (hw->chip_type) {
	case ATC20K1:
		switch (type) {
		case SPDIFOO:	return 0;
		case SPDIFIO:	return 0;
		case SPDIFI1:	return 1;
		case LINEO1:	return 4;
		case LINEO2:	return 7;
		case LINEO3:	return 5;
		case LINEO4:	return 6;
		case LINEIM:	return 7;
		default:	return -EINVAL;
		}
	case ATC20K2:
		switch (type) {
		case SPDIFOO:	return 0;
		case SPDIFIO:	return 0;
		case LINEO1:	return 4;
		case LINEO2:	return 7;
		case LINEO3:	return 5;
		case LINEO4:	return 6;
		case LINEIM:	return 4;
		default:	return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}