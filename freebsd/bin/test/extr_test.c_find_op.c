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
 int OPERAND ; 
 int find_op_1char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int find_op_2char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ops1 ; 
 int /*<<< orphan*/  ops2 ; 
 int /*<<< orphan*/  opsm1 ; 
 int /*<<< orphan*/  opsm2 ; 

__attribute__((used)) static int
find_op(const char *s)
{
	if (s[0] == '\0')
		return OPERAND;
	else if (s[1] == '\0')
		return find_op_1char(ops1, (&ops1)[1], s);
	else if (s[2] == '\0')
		return s[0] == '-' ? find_op_1char(opsm1, (&opsm1)[1], s + 1) :
		    find_op_2char(ops2, (&ops2)[1], s);
	else if (s[3] == '\0')
		return s[0] == '-' ? find_op_2char(opsm2, (&opsm2)[1], s + 1) :
		    OPERAND;
	else
		return OPERAND;
}