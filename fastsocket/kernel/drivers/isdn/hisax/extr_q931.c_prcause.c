#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_2__ {int nr; char* edescr; } ;

/* Variables and functions */
 int CVSIZE ; 
 TYPE_1__* cvlist ; 
 int /*<<< orphan*/  prbits (char*,int,int,int) ; 
 int* skipext (int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static
int
prcause(char *dest, u_char * p)
{
	u_char *end;
	char *dp = dest;
	int i, cause;

	end = p + p[1] + 1;
	p += 2;
	dp += sprintf(dp, "    coding ");
	dp += prbits(dp, *p, 7, 2);
	dp += sprintf(dp, " location ");
	dp += prbits(dp, *p, 4, 4);
	*dp++ = '\n';
	p = skipext(p);

	cause = 0x7f & *p++;

	/* locate cause value */
	for (i = 0; i < CVSIZE; i++)
		if (cvlist[i].nr == cause)
			break;

	/* display cause value if it exists */
	if (i == CVSIZE)
		dp += sprintf(dp, "Unknown cause type %x!\n", cause);
	else
		dp += sprintf(dp, "  cause value %x : %s \n", cause, cvlist[i].edescr);

	while (!0) {
		if (p > end)
			break;
		dp += sprintf(dp, "    diag attribute %d ", *p++ & 0x7f);
		dp += sprintf(dp, " rej %d ", *p & 0x7f);
		if (*p & 0x80) {
			*dp++ = '\n';
			break;
		} else
			dp += sprintf(dp, " av %d\n", (*++p) & 0x7f);
	}
	return (dp - dest);

}