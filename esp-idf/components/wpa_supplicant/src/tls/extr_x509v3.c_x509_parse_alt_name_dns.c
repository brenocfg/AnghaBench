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
typedef  int /*<<< orphan*/  u8 ;
struct x509_name {char* dns; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 size_t os_strlen (char*) ; 
 scalar_t__ os_zalloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int x509_parse_alt_name_dns(struct x509_name *name,
				   const u8 *pos, size_t len)
{
	/* dNSName IA5String */
	wpa_hexdump_ascii(MSG_MSGDUMP, "X509: altName - dNSName", pos, len);
	os_free(name->dns);
	name->dns = (char *)os_zalloc(len + 1);
	if (name->dns == NULL)
		return -1;
	os_memcpy(name->dns, pos, len);
	if (os_strlen(name->dns) != len) {
		wpa_printf(MSG_INFO, "X509: Reject certificate with "
			   "embedded NUL byte in dNSName (%s[NUL])",
			   name->dns);
		os_free(name->dns);
		name->dns = NULL;
		return -1;
	}
	return 0;
}