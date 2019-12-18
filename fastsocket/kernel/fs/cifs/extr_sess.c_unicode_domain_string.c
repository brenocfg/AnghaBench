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
struct cifs_ses {int /*<<< orphan*/ * domainName; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int cifs_strtoUCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct nls_table const*) ; 

__attribute__((used)) static void unicode_domain_string(char **pbcc_area, struct cifs_ses *ses,
				   const struct nls_table *nls_cp)
{
	char *bcc_ptr = *pbcc_area;
	int bytes_ret = 0;

	/* copy domain */
	if (ses->domainName == NULL) {
		/* Sending null domain better than using a bogus domain name (as
		we did briefly in 2.6.18) since server will use its default */
		*bcc_ptr = 0;
		*(bcc_ptr+1) = 0;
		bytes_ret = 0;
	} else
		bytes_ret = cifs_strtoUCS((__le16 *) bcc_ptr, ses->domainName,
					  256, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2;  /* account for null terminator */

	*pbcc_area = bcc_ptr;
}