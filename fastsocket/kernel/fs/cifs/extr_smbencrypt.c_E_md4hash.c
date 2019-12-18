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
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  _my_mbstowcs (scalar_t__*,unsigned char const*,int) ; 
 int _my_wcslen (scalar_t__*) ; 
 int mdfour (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

int
E_md4hash(const unsigned char *passwd, unsigned char *p16)
{
	int rc;
	int len;
	__u16 wpwd[129];

	/* Password cannot be longer than 128 characters */
	if (passwd) {
		len = strlen((char *) passwd);
		if (len > 128)
			len = 128;

		/* Password must be converted to NT unicode */
		_my_mbstowcs(wpwd, passwd, len);
	} else
		len = 0;

	wpwd[len] = 0;	/* Ensure string is null terminated */
	/* Calculate length in bytes */
	len = _my_wcslen(wpwd) * sizeof(__u16);

	rc = mdfour(p16, (unsigned char *) wpwd, len);
	memset(wpwd, 0, 129 * 2);

	return rc;
}