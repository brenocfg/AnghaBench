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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int EOF ; 
 int input_getc () ; 
 int /*<<< orphan*/  input_ungetc (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isxdigit (int) ; 
 scalar_t__ numval ; 
 int /*<<< orphan*/  report (char*) ; 

__attribute__((used)) static void
input_getnum(u_int base, u_int flen)
{
	int c;
	u_int cnt;

	cnt = 0;
	numval = 0;
	while (flen == 0 || cnt < flen) {
		if ((c = input_getc()) == EOF) {
			if (cnt == 0)
				report("bad number");
			return;
		}
		if (isdigit(c)) {
			if (base == 8 && (c == '8' || c == '9')) {
				input_ungetc(c);
				if (cnt == 0)
					report("bad number");
				return;
			}
			numval = numval * base + (c - '0');
		} else if (base == 16 && isxdigit(c)) {
			if (islower(c))
				numval = numval * base + (c - 'a' + 10);
			else
				numval = numval * base + (c - 'A' + 10);
		} else {
			input_ungetc(c);
			if (cnt == 0)
				report("bad number");
			return;
		}
		cnt++;
	}
}