#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ndigi; scalar_t__* repeated; int /*<<< orphan*/  const* calls; } ;
typedef  TYPE_1__ ax25_digi ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 int AX25_ADDR_LEN ; 
 unsigned char AX25_CBIT ; 
 int AX25_COMMAND ; 
 unsigned char AX25_EBIT ; 
 unsigned char AX25_ESSID_SPARE ; 
 unsigned char AX25_HBIT ; 
 int AX25_MODULUS ; 
 int AX25_RESPONSE ; 
 unsigned char AX25_SSSID_SPARE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 

int ax25_addr_build(unsigned char *buf, const ax25_address *src,
	const ax25_address *dest, const ax25_digi *d, int flag, int modulus)
{
	int len = 0;
	int ct  = 0;

	memcpy(buf, dest, AX25_ADDR_LEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] |= AX25_SSSID_SPARE;

	if (flag == AX25_COMMAND) buf[6] |= AX25_CBIT;

	buf += AX25_ADDR_LEN;
	len += AX25_ADDR_LEN;

	memcpy(buf, src, AX25_ADDR_LEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] &= ~AX25_SSSID_SPARE;

	if (modulus == AX25_MODULUS)
		buf[6] |= AX25_SSSID_SPARE;
	else
		buf[6] |= AX25_ESSID_SPARE;

	if (flag == AX25_RESPONSE) buf[6] |= AX25_CBIT;

	/*
	 *	Fast path the normal digiless path
	 */
	if (d == NULL || d->ndigi == 0) {
		buf[6] |= AX25_EBIT;
		return 2 * AX25_ADDR_LEN;
	}

	buf += AX25_ADDR_LEN;
	len += AX25_ADDR_LEN;

	while (ct < d->ndigi) {
		memcpy(buf, &d->calls[ct], AX25_ADDR_LEN);

		if (d->repeated[ct])
			buf[6] |= AX25_HBIT;
		else
			buf[6] &= ~AX25_HBIT;

		buf[6] &= ~AX25_EBIT;
		buf[6] |= AX25_SSSID_SPARE;

		buf += AX25_ADDR_LEN;
		len += AX25_ADDR_LEN;
		ct++;
	}

	buf[-1] |= AX25_EBIT;

	return len;
}