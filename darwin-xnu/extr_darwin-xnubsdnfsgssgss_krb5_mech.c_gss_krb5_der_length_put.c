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
typedef  void* uint8_t ;

/* Variables and functions */
 int gss_krb5_der_length_size (int) ; 

__attribute__((used)) static void
gss_krb5_der_length_put(uint8_t **pp, int len)
{
	int sz = gss_krb5_der_length_size(len);
	uint8_t *p = *pp;

	if (sz == 1) {
		*p++ = (uint8_t) len;
	} else {
		*p++ = (uint8_t) ((sz-1) | 0x80);
		sz -= 1;
		while (sz--)
			*p++ = (uint8_t) ((len >> (sz * 8)) & 0xff);
	}

	*pp = p;
}