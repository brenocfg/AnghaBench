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
struct TYPE_2__ {int tail; char* string; } ;
struct filter_parse_state {TYPE_1__ operand; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_FILTER_STR_VAL ; 

__attribute__((used)) static inline int append_operand_char(struct filter_parse_state *ps, char c)
{
	if (ps->operand.tail == MAX_FILTER_STR_VAL - 1)
		return -EINVAL;

	ps->operand.string[ps->operand.tail++] = c;

	return 0;
}