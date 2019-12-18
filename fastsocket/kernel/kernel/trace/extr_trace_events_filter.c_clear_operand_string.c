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
struct TYPE_2__ {scalar_t__ tail; int /*<<< orphan*/  string; } ;
struct filter_parse_state {TYPE_1__ operand; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FILTER_STR_VAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_operand_string(struct filter_parse_state *ps)
{
	memset(ps->operand.string, '\0', MAX_FILTER_STR_VAL);
	ps->operand.tail = 0;
}