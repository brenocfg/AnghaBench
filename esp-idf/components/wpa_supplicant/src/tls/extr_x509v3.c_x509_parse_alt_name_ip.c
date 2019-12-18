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
struct x509_name {size_t ip_len; int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int x509_parse_alt_name_ip(struct x509_name *name,
				       const u8 *pos, size_t len)
{
	/* iPAddress OCTET STRING */
	wpa_hexdump(MSG_MSGDUMP, "X509: altName - iPAddress", pos, len);
	os_free(name->ip);
	name->ip = os_malloc(len);
	if (name->ip == NULL)
		return -1;
	os_memcpy(name->ip, pos, len);
	name->ip_len = len;
	return 0;
}