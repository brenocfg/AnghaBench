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
struct slgt_info {int gpio_present; int /*<<< orphan*/  init_error; } ;
typedef  int /*<<< orphan*/  patterns ;

/* Variables and functions */
 int /*<<< orphan*/  BDR ; 
 int BIT5 ; 
 int /*<<< orphan*/  DiagStatus_AddressFailure ; 
 int ENODEV ; 
 int /*<<< orphan*/  JCR ; 
 int /*<<< orphan*/  TIR ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int register_test(struct slgt_info *info)
{
	static unsigned short patterns[] =
		{0x0000, 0xffff, 0xaaaa, 0x5555, 0x6969, 0x9696};
	static unsigned int count = sizeof(patterns)/sizeof(patterns[0]);
	unsigned int i;
	int rc = 0;

	for (i=0 ; i < count ; i++) {
		wr_reg16(info, TIR, patterns[i]);
		wr_reg16(info, BDR, patterns[(i+1)%count]);
		if ((rd_reg16(info, TIR) != patterns[i]) ||
		    (rd_reg16(info, BDR) != patterns[(i+1)%count])) {
			rc = -ENODEV;
			break;
		}
	}
	info->gpio_present = (rd_reg32(info, JCR) & BIT5) ? 1 : 0;
	info->init_error = rc ? 0 : DiagStatus_AddressFailure;
	return rc;
}