#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int code_min; int code_max; int position; } ;
typedef  TYPE_1__ tre_literal_t ;
struct literals {int dummy; } ;

/* Variables and functions */
 scalar_t__ tre_islower (int) ; 
 scalar_t__ tre_isupper (int) ; 
 TYPE_1__* tre_new_lit (struct literals*) ; 
 int tre_tolower (int) ; 
 int tre_toupper (int) ; 

__attribute__((used)) static int add_icase_literals(struct literals *ls, int min, int max)
{
	tre_literal_t *lit;
	int b, e, c;
	for (c=min; c<=max; ) {
		/* assumes islower(c) and isupper(c) are exclusive
		   and toupper(c)!=c if islower(c).
		   multiple opposite case characters are not supported */
		if (tre_islower(c)) {
			b = e = tre_toupper(c);
			for (c++, e++; c<=max; c++, e++)
				if (tre_toupper(c) != e) break;
		} else if (tre_isupper(c)) {
			b = e = tre_tolower(c);
			for (c++, e++; c<=max; c++, e++)
				if (tre_tolower(c) != e) break;
		} else {
			c++;
			continue;
		}
		lit = tre_new_lit(ls);
		if (!lit)
			return -1;
		lit->code_min = b;
		lit->code_max = e-1;
		lit->position = -1;
	}
	return 0;
}