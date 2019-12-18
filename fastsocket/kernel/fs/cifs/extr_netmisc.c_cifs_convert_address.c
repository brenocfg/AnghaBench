#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; void* sin6_family; TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {void* sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int cifs_inet_pton (void*,char const*,int,int /*<<< orphan*/ *) ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

int
cifs_convert_address(struct sockaddr *dst, const char *src, int len)
{
	int rc, alen, slen;
	const char *pct;
	char scope_id[13];
	struct sockaddr_in *s4 = (struct sockaddr_in *) dst;
	struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) dst;

	/* IPv4 address */
	if (cifs_inet_pton(AF_INET, src, len, &s4->sin_addr.s_addr)) {
		s4->sin_family = AF_INET;
		return 1;
	}

	/* attempt to exclude the scope ID from the address part */
	pct = memchr(src, '%', len);
	alen = pct ? pct - src : len;

	rc = cifs_inet_pton(AF_INET6, src, alen, &s6->sin6_addr.s6_addr);
	if (!rc)
		return rc;

	s6->sin6_family = AF_INET6;
	if (pct) {
		/* grab the scope ID */
		slen = len - (alen + 1);
		if (slen <= 0 || slen > 12)
			return 0;
		memcpy(scope_id, pct + 1, slen);
		scope_id[slen] = '\0';

		rc = kstrtouint(scope_id, 0, &s6->sin6_scope_id);
		rc = (rc == 0) ? 1 : 0;
	}

	return rc;
}