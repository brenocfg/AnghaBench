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

/* Variables and functions */
 int GETWORD (unsigned char*) ; 
 char* last_cmd ; 
 int mask ; 
 unsigned int mdest ; 
 unsigned int mend ; 
 int mread (unsigned int,unsigned char*,int) ; 
 int mval ; 
 int /*<<< orphan*/  printf (char*,unsigned int,int) ; 
 int /*<<< orphan*/  scanhex (void*) ; 
 char termch ; 

__attribute__((used)) static void
memlocate(void)
{
	unsigned a, n;
	unsigned char val[4];

	last_cmd = "ml";
	scanhex((void *)&mdest);
	if (termch != '\n') {
		termch = 0;
		scanhex((void *)&mend);
		if (termch != '\n') {
			termch = 0;
			scanhex((void *)&mval);
			mask = ~0;
			if (termch != '\n') termch = 0;
			scanhex((void *)&mask);
		}
	}
	n = 0;
	for (a = mdest; a < mend; a += 4) {
		if (mread(a, val, 4) == 4
			&& ((GETWORD(val) ^ mval) & mask) == 0) {
			printf("%.16x:  %.16x\n", a, GETWORD(val));
			if (++n >= 10)
				break;
		}
	}
}