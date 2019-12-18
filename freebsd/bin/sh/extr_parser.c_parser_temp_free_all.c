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
struct parser_temp {struct parser_temp* data; struct parser_temp* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  ckfree (struct parser_temp*) ; 
 struct parser_temp* parser_temp ; 

__attribute__((used)) static void
parser_temp_free_all(void)
{
	struct parser_temp *t;

	INTOFF;
	while (parser_temp != NULL) {
		t = parser_temp;
		parser_temp = t->next;
		ckfree(t->data);
		ckfree(t);
	}
	INTON;
}