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
typedef  int /*<<< orphan*/  u32 ;
struct rsxx_cardinfo {scalar_t__ regmap; int /*<<< orphan*/  eeh_state; } ;

/* Variables and functions */
 scalar_t__ CREG_DATA (int) ; 
 int EIO ; 
 scalar_t__ LITTLE_ENDIAN ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_to_creg_data(struct rsxx_cardinfo *card,
			      int cnt8,
			      void *buf,
			      unsigned int stream)
{
	int i = 0;
	u32 *data = buf;

	if (unlikely(card->eeh_state))
		return -EIO;

	for (i = 0; cnt8 > 0; i++, cnt8 -= 4) {
		/*
		 * Firmware implementation makes it necessary to byte swap on
		 * little endian processors.
		 */
		if (LITTLE_ENDIAN && stream)
			iowrite32be(data[i], card->regmap + CREG_DATA(i));
		else
			iowrite32(data[i], card->regmap + CREG_DATA(i));
	}

	return 0;
}