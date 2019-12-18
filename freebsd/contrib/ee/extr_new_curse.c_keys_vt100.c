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
struct KEY_STACK {TYPE_1__* element; struct KEY_STACK* next; } ;
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 struct KEY_STACK* KEY_TOS ; 
 int Max_Key_len ; 
 scalar_t__ malloc (int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* vt100 ; 

void
keys_vt100()
{
	int counter;
	int Klen;
	struct KEY_STACK *Spoint;

	Spoint = KEY_TOS;
	while (Spoint->next != NULL)
		Spoint = Spoint->next;
	for (counter = 0; vt100[counter].length != 0; counter++)
	{
		Spoint->next = (struct KEY_STACK *) malloc(sizeof(struct KEY_STACK));
		Spoint = Spoint->next;
		Spoint->next = NULL;
		Spoint->element = &vt100[counter];
		Klen = strlen(Spoint->element->string);
		if (Klen > Max_Key_len)
			Max_Key_len = Klen;
	}
}