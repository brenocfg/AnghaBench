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
typedef  int uint32_t ;
struct stub_state {size_t i; int* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void stub_state_push_array(struct stub_state *s, uint32_t size)
{
	s->i++;
	s->stack[s->i] = 2;
	s->i++;
	s->stack[s->i] = size;
	printf("[");
}