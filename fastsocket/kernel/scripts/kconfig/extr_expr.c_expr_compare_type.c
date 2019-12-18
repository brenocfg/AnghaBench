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
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  E_AND 133 
#define  E_EQUAL 132 
#define  E_LIST 131 
#define  E_NOT 130 
#define  E_OR 129 
#define  E_UNEQUAL 128 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int expr_compare_type(enum expr_type t1, enum expr_type t2)
{
#if 0
	return 1;
#else
	if (t1 == t2)
		return 0;
	switch (t1) {
	case E_EQUAL:
	case E_UNEQUAL:
		if (t2 == E_NOT)
			return 1;
	case E_NOT:
		if (t2 == E_AND)
			return 1;
	case E_AND:
		if (t2 == E_OR)
			return 1;
	case E_OR:
		if (t2 == E_LIST)
			return 1;
	case E_LIST:
		if (t2 == 0)
			return 1;
	default:
		return -1;
	}
	printf("[%dgt%d?]", t1, t2);
	return 0;
#endif
}