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
struct rmsgpack_dom_value {int dummy; } ;
struct dom_reader_state {size_t i; struct rmsgpack_dom_value** stack; } ;

/* Variables and functions */

__attribute__((used)) static struct rmsgpack_dom_value *dom_reader_state_pop(struct dom_reader_state *s)
{
	struct rmsgpack_dom_value *v = s->stack[s->i];
	s->i--;
	return v;
}