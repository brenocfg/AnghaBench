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
typedef  int u8 ;

/* Variables and functions */
 int const V4L2_IDENT_SAA7111 ; 
 int const V4L2_IDENT_SAA7111A ; 
#define  V4L2_IDENT_SAA7113 131 
#define  V4L2_IDENT_SAA7114 130 
#define  V4L2_IDENT_SAA7115 129 
#define  V4L2_IDENT_SAA7118 128 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int saa711x_has_reg(const int id, const u8 reg)
{
	if (id == V4L2_IDENT_SAA7111)
		return reg < 0x20 && reg != 0x01 && reg != 0x0f &&
		       (reg < 0x13 || reg > 0x19) && reg != 0x1d && reg != 0x1e;
	if (id == V4L2_IDENT_SAA7111A)
		return reg < 0x20 && reg != 0x01 && reg != 0x0f &&
		       reg != 0x14 && reg != 0x18 && reg != 0x19 &&
		       reg != 0x1d && reg != 0x1e;

	/* common for saa7113/4/5/8 */
	if (unlikely((reg >= 0x3b && reg <= 0x3f) || reg == 0x5c || reg == 0x5f ||
	    reg == 0xa3 || reg == 0xa7 || reg == 0xab || reg == 0xaf || (reg >= 0xb5 && reg <= 0xb7) ||
	    reg == 0xd3 || reg == 0xd7 || reg == 0xdb || reg == 0xdf || (reg >= 0xe5 && reg <= 0xe7) ||
	    reg == 0x82 || (reg >= 0x89 && reg <= 0x8e)))
		return 0;

	switch (id) {
	case V4L2_IDENT_SAA7113:
		return reg != 0x14 && (reg < 0x18 || reg > 0x1e) && (reg < 0x20 || reg > 0x3f) &&
		       reg != 0x5d && reg < 0x63;
	case V4L2_IDENT_SAA7114:
		return (reg < 0x1a || reg > 0x1e) && (reg < 0x20 || reg > 0x2f) &&
		       (reg < 0x63 || reg > 0x7f) && reg != 0x33 && reg != 0x37 &&
		       reg != 0x81 && reg < 0xf0;
	case V4L2_IDENT_SAA7115:
		return (reg < 0x20 || reg > 0x2f) && reg != 0x65 && (reg < 0xfc || reg > 0xfe);
	case V4L2_IDENT_SAA7118:
		return (reg < 0x1a || reg > 0x1d) && (reg < 0x20 || reg > 0x22) &&
		       (reg < 0x26 || reg > 0x28) && reg != 0x33 && reg != 0x37 &&
		       (reg < 0x63 || reg > 0x7f) && reg != 0x81 && reg < 0xf0;
	}
	return 1;
}