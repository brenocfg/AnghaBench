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
typedef  size_t u_int ;
struct asn_oid {size_t len; int* subs; } ;

/* Variables and functions */
 size_t ASN_MAXOIDLEN ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *
asn_oid2str_r(const struct asn_oid *oid, char *buf)
{
	u_int len, i;
	char *ptr;

	if ((len = oid->len) > ASN_MAXOIDLEN)
		len = ASN_MAXOIDLEN;
	buf[0] = '\0';
	for (i = 0, ptr = buf; i < len; i++) {
		if (i > 0)
			*ptr++ = '.';
		ptr += sprintf(ptr, "%u", oid->subs[i]);
	}
	return (buf);
}