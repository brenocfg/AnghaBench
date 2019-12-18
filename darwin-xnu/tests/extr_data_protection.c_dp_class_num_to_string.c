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
#define  PROTECTION_CLASS_A 133 
#define  PROTECTION_CLASS_B 132 
#define  PROTECTION_CLASS_C 131 
#define  PROTECTION_CLASS_D 130 
#define  PROTECTION_CLASS_E 129 
#define  PROTECTION_CLASS_F 128 

char*
dp_class_num_to_string(int num) {
	switch(num) {
		case 0:
			return "unclassed";
		case PROTECTION_CLASS_A:
			return "class A";
		case PROTECTION_CLASS_B:
			return "class B";
		case PROTECTION_CLASS_C:
			return "class C";
		case PROTECTION_CLASS_D:
			return "class D";
		case PROTECTION_CLASS_E:
			return "class E";
		case PROTECTION_CLASS_F:
			return "class F";
		default:
			return "<unknown class>";
	}
}