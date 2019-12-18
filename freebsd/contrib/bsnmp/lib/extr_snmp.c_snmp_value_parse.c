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
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * subs; } ;
struct TYPE_3__ {char* octets; int len; } ;
union snmp_values {void* counter64; int /*<<< orphan*/  uint32; int /*<<< orphan*/  ipaddress; TYPE_2__ oid; TYPE_1__ octetstring; int /*<<< orphan*/  integer; } ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
typedef  char u_char ;
struct hostent {int /*<<< orphan*/  h_addr; int /*<<< orphan*/  h_addrtype; } ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ASN_MAXID ; 
 int /*<<< orphan*/  ASN_MAXOIDLEN ; 
#define  SNMP_SYNTAX_COUNTER 139 
#define  SNMP_SYNTAX_COUNTER64 138 
#define  SNMP_SYNTAX_ENDOFMIBVIEW 137 
#define  SNMP_SYNTAX_GAUGE 136 
#define  SNMP_SYNTAX_INTEGER 135 
#define  SNMP_SYNTAX_IPADDRESS 134 
#define  SNMP_SYNTAX_NOSUCHINSTANCE 133 
#define  SNMP_SYNTAX_NOSUCHOBJECT 132 
#define  SNMP_SYNTAX_NULL 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int /*<<< orphan*/  STUFFC (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 struct hostent* gethostbyname2 (char const*,int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  isupper (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strtoll (char const*,char**,int /*<<< orphan*/ ) ; 
 int strtoul (char const*,char**,int) ; 
 void* strtoull (char const*,char**,int /*<<< orphan*/ ) ; 

int
snmp_value_parse(const char *str, enum snmp_syntax syntax, union snmp_values *v)
{
	char *end;

	switch (syntax) {

	  case SNMP_SYNTAX_NULL:
	  case SNMP_SYNTAX_NOSUCHOBJECT:
	  case SNMP_SYNTAX_NOSUCHINSTANCE:
	  case SNMP_SYNTAX_ENDOFMIBVIEW:
		if (*str != '\0')
			return (-1);
		return (0);

	  case SNMP_SYNTAX_INTEGER:
		v->integer = strtoll(str, &end, 0);
		if (*end != '\0')
			return (-1);
		return (0);

	  case SNMP_SYNTAX_OCTETSTRING:
	    {
		u_long len;	/* actual length of string */
		u_long alloc;	/* allocate length of string */
		u_char *octs;	/* actual octets */
		u_long oct;	/* actual octet */
		u_char *nocts;	/* to avoid memory leak */
		u_char c;	/* actual character */

# define STUFFC(C)							\
		if (alloc == len) {					\
			alloc += 100;					\
			if ((nocts = realloc(octs, alloc)) == NULL) {	\
				free(octs);				\
				return (-1);				\
			}						\
			octs = nocts;					\
		}							\
		octs[len++] = (C);

		len = alloc = 0;
		octs = NULL;

		if (*str == '"') {
			str++;
			while((c = *str++) != '\0') {
				if (c == '"') {
					if (*str != '\0') {
						free(octs);
						return (-1);
					}
					break;
				}
				if (c == '\\') {
					switch (c = *str++) {

					  case '\\':
						break;
					  case 'a':
						c = '\a';
						break;
					  case 'b':
						c = '\b';
						break;
					  case 'f':
						c = '\f';
						break;
					  case 'n':
						c = '\n';
						break;
					  case 'r':
						c = '\r';
						break;
					  case 't':
						c = '\t';
						break;
					  case 'v':
						c = '\v';
						break;
					  case 'x':
						c = 0;
						if (!isxdigit(*str))
							break;
						if (isdigit(*str))
							c = *str++ - '0';
						else if (isupper(*str))
							c = *str++ - 'A' + 10;
						else
							c = *str++ - 'a' + 10;
						if (!isxdigit(*str))
							break;
						if (isdigit(*str))
							c += *str++ - '0';
						else if (isupper(*str))
							c += *str++ - 'A' + 10;
						else
							c += *str++ - 'a' + 10;
						break;
					  case '0': case '1': case '2':
					  case '3': case '4': case '5':
					  case '6': case '7':
						c = *str++ - '0';
						if (*str < '0' || *str > '7')
							break;
						c = *str++ - '0';
						if (*str < '0' || *str > '7')
							break;
						c = *str++ - '0';
						break;
					  default:
						break;
					}
				}
				STUFFC(c);
			}
		} else {
			while (*str != '\0') {
				oct = strtoul(str, &end, 16);
				str = end;
				if (oct > 0xff) {
					free(octs);
					return (-1);
				}
				STUFFC(oct);
				if (*str == ':')
					str++;
				else if(*str != '\0') {
					free(octs);
					return (-1);
				}
			}
		}
		v->octetstring.octets = octs;
		v->octetstring.len = len;
		return (0);
# undef STUFFC
	    }

	  case SNMP_SYNTAX_OID:
	    {
		u_long subid;

		v->oid.len = 0;

		for (;;) {
			if (v->oid.len == ASN_MAXOIDLEN)
				return (-1);
			subid = strtoul(str, &end, 10);
			str = end;
			if (subid > ASN_MAXID)
				return (-1);
			v->oid.subs[v->oid.len++] = (asn_subid_t)subid;
			if (*str == '\0')
				break;
			if (*str != '.')
				return (-1);
			str++;
		}
		return (0);
	    }

	  case SNMP_SYNTAX_IPADDRESS:
	    {
		struct hostent *he;

		if (inet_pton(AF_INET, str, &v->ipaddress) == 1)
			return (0);
		if ((he = gethostbyname2(str, AF_INET)) == NULL)
			return (-1);
		if (he->h_addrtype != AF_INET)
			return (-1);

		memcpy(v->ipaddress, he->h_addr, sizeof(v->ipaddress));

		return (0);
	    }

	  case SNMP_SYNTAX_COUNTER:
	  case SNMP_SYNTAX_GAUGE:
	  case SNMP_SYNTAX_TIMETICKS:
	    {
		uint64_t sub;

		sub = strtoull(str, &end, 0);
		if (*end != '\0' || sub > 0xffffffff)
			return (-1);
		v->uint32 = (uint32_t)sub;
		return (0);
	    }

	  case SNMP_SYNTAX_COUNTER64:
		v->counter64 = strtoull(str, &end, 0);
		if (*end != '\0')
			return (-1);
		return (0);
	}
	abort();
}