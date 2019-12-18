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
 int /*<<< orphan*/  BANK_BP ; 
 int /*<<< orphan*/  NOP () ; 
 unsigned int PT_BP ; 
 int /*<<< orphan*/  SPEC_REG_RD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPEC_REG_SRS ; 
 int /*<<< orphan*/  SPEC_REG_WR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUPP_BANK_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPP_REG_RD (int,long) ; 
 long bp_owner ; 

__attribute__((used)) static long get_debugreg(long pid, unsigned int regno)
{
	register int old_srs;
	register long data;

	if (pid != bp_owner) {
		return 0;
	}

	/* Remember old SRS. */
	SPEC_REG_RD(SPEC_REG_SRS, old_srs);
	/* Switch to BP bank. */
	SUPP_BANK_SEL(BANK_BP);

	switch (regno - PT_BP) {
	case 0:
		SUPP_REG_RD(0, data); break;
	case 1:
	case 2:
		/* error return value? */
		data = 0;
		break;
	case 3:
		SUPP_REG_RD(3, data); break;
	case 4:
		SUPP_REG_RD(4, data); break;
	case 5:
		SUPP_REG_RD(5, data); break;
	case 6:
		SUPP_REG_RD(6, data); break;
	case 7:
		SUPP_REG_RD(7, data); break;
	case 8:
		SUPP_REG_RD(8, data); break;
	case 9:
		SUPP_REG_RD(9, data); break;
	case 10:
		SUPP_REG_RD(10, data); break;
	case 11:
		SUPP_REG_RD(11, data); break;
	case 12:
		SUPP_REG_RD(12, data); break;
	case 13:
		SUPP_REG_RD(13, data); break;
	case 14:
		SUPP_REG_RD(14, data); break;
	default:
		/* error return value? */
		data = 0;
	}

	/* Restore SRS. */
	SPEC_REG_WR(SPEC_REG_SRS, old_srs);
	/* Just for show. */
	NOP();
	NOP();
	NOP();

	return data;
}