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
struct st {int op; } ;

/* Variables and functions */

__attribute__((used)) static const char *parseop(struct st *st, const char *s)
{
	static const char opch[11] = "|&=!><+-*%/";
	static const char opch2[6] = "|&====";
	int i;
	for (i=0; i<11; i++)
		if (*s == opch[i]) {
			/* note: >,< are accepted with or without = */
			if (i<6 && s[1] == opch2[i]) {
				st->op = i;
				return s+2;
			}
			if (i>=4) {
				st->op = i+2;
				return s+1;
			}
			break;
		}
	st->op = 13;
	return s;
}