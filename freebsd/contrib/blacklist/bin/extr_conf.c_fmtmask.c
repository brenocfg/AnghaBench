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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
#define  FEQUAL 129 
#define  FSTAR 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static const char *
fmtmask(char *b, size_t l, int fam, int mask)
{
	char buf[128];

	switch (mask) {
	case FSTAR:
		return "";
	case FEQUAL:
		if (strcmp(b, "=") == 0)
			return "";
		else {
			strlcat(b, "/=", l);
			return b;
		}
	default:
		break;
	}

	switch (fam) {
	case AF_INET:
		if (mask == 32)
			return "";
		break;
	case AF_INET6:
		if (mask == 128)
			return "";
		break;
	default:
		break;
	}

	snprintf(buf, sizeof(buf), "/%d", mask);
	strlcat(b, buf, l);
	return b;
}