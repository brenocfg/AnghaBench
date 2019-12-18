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
typedef  int /*<<< orphan*/  tmp ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  in_aton (char const*) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ *,int) ; 
 unsigned long simple_strtol (char const*,char**,int) ; 
 unsigned long simple_strtoul (char const*,char**,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static unsigned int scan_ip6(const char *s, char ip[16])
{
	unsigned int i;
	unsigned int len = 0;
	unsigned long u;
	char suffix[16];
	unsigned int prefixlen = 0;
	unsigned int suffixlen = 0;
	__be32 tmp;
	char *pos;

	for (i = 0; i < 16; i++)
		ip[i] = 0;

	for (;;) {
		if (*s == ':') {
			len++;
			if (s[1] == ':') {	/* Found "::", skip to part 2 */
				s += 2;
				len++;
				break;
			}
			s++;
		}

		u = simple_strtoul(s, &pos, 16);
		i = pos - s;
		if (!i)
			return 0;
		if (prefixlen == 12 && s[i] == '.') {

			/* the last 4 bytes may be written as IPv4 address */

			tmp = in_aton(s);
			memcpy((struct in_addr *)(ip + 12), &tmp, sizeof(tmp));
			return i + len;
		}
		ip[prefixlen++] = (u >> 8);
		ip[prefixlen++] = (u & 255);
		s += i;
		len += i;
		if (prefixlen == 16)
			return len;
	}

/* part 2, after "::" */
	for (;;) {
		if (*s == ':') {
			if (suffixlen == 0)
				break;
			s++;
			len++;
		} else if (suffixlen != 0)
			break;

		u = simple_strtol(s, &pos, 16);
		i = pos - s;
		if (!i) {
			if (*s)
				len--;
			break;
		}
		if (suffixlen + prefixlen <= 12 && s[i] == '.') {
			tmp = in_aton(s);
			memcpy((struct in_addr *)(suffix + suffixlen), &tmp,
			       sizeof(tmp));
			suffixlen += 4;
			len += strlen(s);
			break;
		}
		suffix[suffixlen++] = (u >> 8);
		suffix[suffixlen++] = (u & 255);
		s += i;
		len += i;
		if (prefixlen + suffixlen == 16)
			break;
	}
	for (i = 0; i < suffixlen; i++)
		ip[16 - suffixlen + i] = suffix[i];
	return len;
}