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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UBIFS_LPT_TYPE_BITS ; 
 int /*<<< orphan*/  dbg_dump_stack () ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int) ; 
 int ubifs_unpack_bits (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_lpt_type(uint8_t **addr, int *pos, int type)
{
	int node_type;

	node_type = ubifs_unpack_bits(addr, pos, UBIFS_LPT_TYPE_BITS);
	if (node_type != type) {
		ubifs_err("invalid type (%d) in LPT node type %d", node_type,
			  type);
		dbg_dump_stack();
		return -EINVAL;
	}
	return 0;
}