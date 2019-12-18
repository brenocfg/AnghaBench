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
struct ubifs_info {int /*<<< orphan*/  pcnt_bits; } ;

/* Variables and functions */
 int UBIFS_LPT_CRC_BYTES ; 
 int /*<<< orphan*/  UBIFS_LPT_TYPE_BITS ; 
 int ubifs_unpack_bits (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_lpt_node_type(const struct ubifs_info *c, uint8_t *buf,
			     int *node_num)
{
	uint8_t *addr = buf + UBIFS_LPT_CRC_BYTES;
	int pos = 0, node_type;

	node_type = ubifs_unpack_bits(&addr, &pos, UBIFS_LPT_TYPE_BITS);
	*node_num = ubifs_unpack_bits(&addr, &pos, c->pcnt_bits);
	return node_type;
}