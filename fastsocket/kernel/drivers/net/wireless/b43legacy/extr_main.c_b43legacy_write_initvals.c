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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; } ;
struct TYPE_2__ {int /*<<< orphan*/  d16; int /*<<< orphan*/  d32; } ;
struct b43legacy_iv {TYPE_1__ data; int /*<<< orphan*/  offset_size; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int B43legacy_IV_32BIT ; 
 int B43legacy_IV_OFFSET_MASK ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EPROTO ; 
 int /*<<< orphan*/  b43legacy_print_fw_helptext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b43legacy_write_initvals(struct b43legacy_wldev *dev,
				    const struct b43legacy_iv *ivals,
				    size_t count,
				    size_t array_size)
{
	const struct b43legacy_iv *iv;
	u16 offset;
	size_t i;
	bool bit32;

	BUILD_BUG_ON(sizeof(struct b43legacy_iv) != 6);
	iv = ivals;
	for (i = 0; i < count; i++) {
		if (array_size < sizeof(iv->offset_size))
			goto err_format;
		array_size -= sizeof(iv->offset_size);
		offset = be16_to_cpu(iv->offset_size);
		bit32 = !!(offset & B43legacy_IV_32BIT);
		offset &= B43legacy_IV_OFFSET_MASK;
		if (offset >= 0x1000)
			goto err_format;
		if (bit32) {
			u32 value;

			if (array_size < sizeof(iv->data.d32))
				goto err_format;
			array_size -= sizeof(iv->data.d32);

			value = get_unaligned_be32(&iv->data.d32);
			b43legacy_write32(dev, offset, value);

			iv = (const struct b43legacy_iv *)((const uint8_t *)iv +
							sizeof(__be16) +
							sizeof(__be32));
		} else {
			u16 value;

			if (array_size < sizeof(iv->data.d16))
				goto err_format;
			array_size -= sizeof(iv->data.d16);

			value = be16_to_cpu(iv->data.d16);
			b43legacy_write16(dev, offset, value);

			iv = (const struct b43legacy_iv *)((const uint8_t *)iv +
							sizeof(__be16) +
							sizeof(__be16));
		}
	}
	if (array_size)
		goto err_format;

	return 0;

err_format:
	b43legacyerr(dev->wl, "Initial Values Firmware file-format error.\n");
	b43legacy_print_fw_helptext(dev->wl);

	return -EPROTO;
}