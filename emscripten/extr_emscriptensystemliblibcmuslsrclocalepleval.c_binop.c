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
struct st {unsigned long r; } ;

/* Variables and functions */

__attribute__((used)) static int binop(struct st *st, int op, unsigned long left)
{
	unsigned long a = left, b = st->r;
	switch (op) {
	case 0: st->r = a||b; return 0;
	case 1: st->r = a&&b; return 0;
	case 2: st->r = a==b; return 0;
	case 3: st->r = a!=b; return 0;
	case 4: st->r = a>=b; return 0;
	case 5: st->r = a<=b; return 0;
	case 6: st->r = a>b; return 0;
	case 7: st->r = a<b; return 0;
	case 8: st->r = a+b; return 0;
	case 9: st->r = a-b; return 0;
	case 10: st->r = a*b; return 0;
	case 11: if (b) {st->r = a%b; return 0;} return 1;
	case 12: if (b) {st->r = a/b; return 0;} return 1;
	}
	return 1;
}