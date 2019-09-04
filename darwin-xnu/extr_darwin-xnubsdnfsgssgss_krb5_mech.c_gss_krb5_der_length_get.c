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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t
gss_krb5_der_length_get(uint8_t **pp)
{
	uint8_t *p = *pp;
	uint32_t flen, len = 0;

	flen = *p & 0x7f;

	if (*p++ & 0x80) {
		if (flen > sizeof(uint32_t))
			return (-1);
		while (flen--)
			len = (len << 8) + *p++;
	} else {
		len = flen;
	}
	*pp = p;
	return (len);
}