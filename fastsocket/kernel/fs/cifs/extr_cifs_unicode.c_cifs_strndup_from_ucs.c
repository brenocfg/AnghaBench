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
struct nls_table {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cifs_from_ucs2 (char*,int /*<<< orphan*/ *,int,int const,struct nls_table const*,int) ; 
 int cifs_ucs2_bytes (int /*<<< orphan*/ *,int const,struct nls_table const*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nls_nullsize (struct nls_table const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strnlen (char const*,int const) ; 

char *
cifs_strndup_from_ucs(const char *src, const int maxlen, const bool is_unicode,
	     const struct nls_table *codepage)
{
	int len;
	char *dst;

	if (is_unicode) {
		len = cifs_ucs2_bytes((__le16 *) src, maxlen, codepage);
		len += nls_nullsize(codepage);
		dst = kmalloc(len, GFP_KERNEL);
		if (!dst)
			return NULL;
		cifs_from_ucs2(dst, (__le16 *) src, len, maxlen, codepage,
			       false);
	} else {
		len = strnlen(src, maxlen);
		len++;
		dst = kmalloc(len, GFP_KERNEL);
		if (!dst)
			return NULL;
		strlcpy(dst, src, len);
	}

	return dst;
}