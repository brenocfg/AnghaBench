#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ubifs_info {int lpt_lebs; int leb_size; int /*<<< orphan*/  ltab_sz; TYPE_1__* ltab; int /*<<< orphan*/  lpt_spc_bits; } ;
struct TYPE_2__ {int free; int dirty; scalar_t__ cmt; scalar_t__ tgc; } ;

/* Variables and functions */
 int EINVAL ; 
 int UBIFS_LPT_CRC_BYTES ; 
 int /*<<< orphan*/  UBIFS_LPT_LTAB ; 
 int check_lpt_crc (void*,int /*<<< orphan*/ ) ; 
 int check_lpt_type (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int ubifs_unpack_bits (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unpack_ltab(const struct ubifs_info *c, void *buf)
{
	uint8_t *addr = buf + UBIFS_LPT_CRC_BYTES;
	int i, pos = 0, err;

	err = check_lpt_type(&addr, &pos, UBIFS_LPT_LTAB);
	if (err)
		return err;
	for (i = 0; i < c->lpt_lebs; i++) {
		int free = ubifs_unpack_bits(&addr, &pos, c->lpt_spc_bits);
		int dirty = ubifs_unpack_bits(&addr, &pos, c->lpt_spc_bits);

		if (free < 0 || free > c->leb_size || dirty < 0 ||
		    dirty > c->leb_size || free + dirty > c->leb_size)
			return -EINVAL;

		c->ltab[i].free = free;
		c->ltab[i].dirty = dirty;
		c->ltab[i].tgc = 0;
		c->ltab[i].cmt = 0;
	}
	err = check_lpt_crc(buf, c->ltab_sz);
	return err;
}