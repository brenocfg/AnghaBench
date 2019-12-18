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
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int,...) ; 
 scalar_t__ COMMON_ASM_INVALID_ASSERT_OPCODE ; 
 scalar_t__ CSTORM_ASSERT_LIST_INDEX_OFFSET ; 
 scalar_t__ CSTORM_ASSERT_LIST_OFFSET (int) ; 
 scalar_t__ REG_RD (struct bnx2x*,scalar_t__) ; 
 char REG_RD8 (struct bnx2x*,scalar_t__) ; 
 int STROM_ASSERT_ARRAY_SIZE ; 
 scalar_t__ TSTORM_ASSERT_LIST_INDEX_OFFSET ; 
 scalar_t__ TSTORM_ASSERT_LIST_OFFSET (int) ; 
 scalar_t__ USTORM_ASSERT_LIST_INDEX_OFFSET ; 
 scalar_t__ USTORM_ASSERT_LIST_OFFSET (int) ; 
 scalar_t__ XSTORM_ASSERT_LIST_INDEX_OFFSET ; 
 scalar_t__ XSTORM_ASSERT_LIST_OFFSET (int) ; 

__attribute__((used)) static int bnx2x_mc_assert(struct bnx2x *bp)
{
	char last_idx;
	int i, rc = 0;
	u32 row0, row1, row2, row3;

	/* XSTORM */
	last_idx = REG_RD8(bp, BAR_XSTRORM_INTMEM +
			   XSTORM_ASSERT_LIST_INDEX_OFFSET);
	if (last_idx)
		BNX2X_ERR("XSTORM_ASSERT_LIST_INDEX 0x%x\n", last_idx);

	/* print the asserts */
	for (i = 0; i < STROM_ASSERT_ARRAY_SIZE; i++) {

		row0 = REG_RD(bp, BAR_XSTRORM_INTMEM +
			      XSTORM_ASSERT_LIST_OFFSET(i));
		row1 = REG_RD(bp, BAR_XSTRORM_INTMEM +
			      XSTORM_ASSERT_LIST_OFFSET(i) + 4);
		row2 = REG_RD(bp, BAR_XSTRORM_INTMEM +
			      XSTORM_ASSERT_LIST_OFFSET(i) + 8);
		row3 = REG_RD(bp, BAR_XSTRORM_INTMEM +
			      XSTORM_ASSERT_LIST_OFFSET(i) + 12);

		if (row0 != COMMON_ASM_INVALID_ASSERT_OPCODE) {
			BNX2X_ERR("XSTORM_ASSERT_INDEX 0x%x = 0x%08x 0x%08x 0x%08x 0x%08x\n",
				  i, row3, row2, row1, row0);
			rc++;
		} else {
			break;
		}
	}

	/* TSTORM */
	last_idx = REG_RD8(bp, BAR_TSTRORM_INTMEM +
			   TSTORM_ASSERT_LIST_INDEX_OFFSET);
	if (last_idx)
		BNX2X_ERR("TSTORM_ASSERT_LIST_INDEX 0x%x\n", last_idx);

	/* print the asserts */
	for (i = 0; i < STROM_ASSERT_ARRAY_SIZE; i++) {

		row0 = REG_RD(bp, BAR_TSTRORM_INTMEM +
			      TSTORM_ASSERT_LIST_OFFSET(i));
		row1 = REG_RD(bp, BAR_TSTRORM_INTMEM +
			      TSTORM_ASSERT_LIST_OFFSET(i) + 4);
		row2 = REG_RD(bp, BAR_TSTRORM_INTMEM +
			      TSTORM_ASSERT_LIST_OFFSET(i) + 8);
		row3 = REG_RD(bp, BAR_TSTRORM_INTMEM +
			      TSTORM_ASSERT_LIST_OFFSET(i) + 12);

		if (row0 != COMMON_ASM_INVALID_ASSERT_OPCODE) {
			BNX2X_ERR("TSTORM_ASSERT_INDEX 0x%x = 0x%08x 0x%08x 0x%08x 0x%08x\n",
				  i, row3, row2, row1, row0);
			rc++;
		} else {
			break;
		}
	}

	/* CSTORM */
	last_idx = REG_RD8(bp, BAR_CSTRORM_INTMEM +
			   CSTORM_ASSERT_LIST_INDEX_OFFSET);
	if (last_idx)
		BNX2X_ERR("CSTORM_ASSERT_LIST_INDEX 0x%x\n", last_idx);

	/* print the asserts */
	for (i = 0; i < STROM_ASSERT_ARRAY_SIZE; i++) {

		row0 = REG_RD(bp, BAR_CSTRORM_INTMEM +
			      CSTORM_ASSERT_LIST_OFFSET(i));
		row1 = REG_RD(bp, BAR_CSTRORM_INTMEM +
			      CSTORM_ASSERT_LIST_OFFSET(i) + 4);
		row2 = REG_RD(bp, BAR_CSTRORM_INTMEM +
			      CSTORM_ASSERT_LIST_OFFSET(i) + 8);
		row3 = REG_RD(bp, BAR_CSTRORM_INTMEM +
			      CSTORM_ASSERT_LIST_OFFSET(i) + 12);

		if (row0 != COMMON_ASM_INVALID_ASSERT_OPCODE) {
			BNX2X_ERR("CSTORM_ASSERT_INDEX 0x%x = 0x%08x 0x%08x 0x%08x 0x%08x\n",
				  i, row3, row2, row1, row0);
			rc++;
		} else {
			break;
		}
	}

	/* USTORM */
	last_idx = REG_RD8(bp, BAR_USTRORM_INTMEM +
			   USTORM_ASSERT_LIST_INDEX_OFFSET);
	if (last_idx)
		BNX2X_ERR("USTORM_ASSERT_LIST_INDEX 0x%x\n", last_idx);

	/* print the asserts */
	for (i = 0; i < STROM_ASSERT_ARRAY_SIZE; i++) {

		row0 = REG_RD(bp, BAR_USTRORM_INTMEM +
			      USTORM_ASSERT_LIST_OFFSET(i));
		row1 = REG_RD(bp, BAR_USTRORM_INTMEM +
			      USTORM_ASSERT_LIST_OFFSET(i) + 4);
		row2 = REG_RD(bp, BAR_USTRORM_INTMEM +
			      USTORM_ASSERT_LIST_OFFSET(i) + 8);
		row3 = REG_RD(bp, BAR_USTRORM_INTMEM +
			      USTORM_ASSERT_LIST_OFFSET(i) + 12);

		if (row0 != COMMON_ASM_INVALID_ASSERT_OPCODE) {
			BNX2X_ERR("USTORM_ASSERT_INDEX 0x%x = 0x%08x 0x%08x 0x%08x 0x%08x\n",
				  i, row3, row2, row1, row0);
			rc++;
		} else {
			break;
		}
	}

	return rc;
}