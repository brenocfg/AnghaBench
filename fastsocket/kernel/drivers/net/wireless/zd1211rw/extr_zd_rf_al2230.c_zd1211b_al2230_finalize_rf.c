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
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {scalar_t__ new_phy_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR12 135 
#define  ZD_CR203 134 
#define  ZD_CR240 133 
#define  ZD_CR77 132 
#define  ZD_CR78 131 
#define  ZD_CR79 130 
#define  ZD_CR80 129 
#define  ZD_CR81 128 
 int /*<<< orphan*/  const ZD_CR9 ; 
 int zd_iowrite16_locked (struct zd_chip*,int,int /*<<< orphan*/  const) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211b_al2230_finalize_rf(struct zd_chip *chip)
{
	int r;
	static const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR80,  0x30 }, { ZD_CR81,  0x30 }, { ZD_CR79,  0x58 },
		{ ZD_CR12,  0xf0 }, { ZD_CR77,  0x1b }, { ZD_CR78,  0x58 },
		{ ZD_CR203, 0x06 },
		{ },

		{ ZD_CR240, 0x80 },
	};

	r = zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	if (r)
		return r;

	/* related to antenna selection? */
	if (chip->new_phy_layout) {
		r = zd_iowrite16_locked(chip, 0xe1, ZD_CR9);
		if (r)
			return r;
	}

	return zd_iowrite16_locked(chip, 0x06, ZD_CR203);
}