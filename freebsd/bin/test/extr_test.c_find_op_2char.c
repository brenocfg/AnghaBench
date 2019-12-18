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
struct t_op {char const* op_text; int op_num; } ;

/* Variables and functions */
 int OPERAND ; 

__attribute__((used)) static int
find_op_2char(const struct t_op *op, const struct t_op *end, const char *s)
{
	while (op != end) {
		if (s[0] == op->op_text[0] && s[1] == op->op_text[1])
			return op->op_num;
		op++;
	}
	return OPERAND;
}