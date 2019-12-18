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
struct dom_reader_state {int i; struct rmsgpack_dom_value** stack; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_DEPTH ; 

__attribute__((used)) static int dom_reader_state_push(struct dom_reader_state *s, struct rmsgpack_dom_value *v)
{
	if ((s->i + 1) == MAX_DEPTH)
		return -ENOMEM;
	s->i++;
	s->stack[s->i] = v;
	return 0;
}