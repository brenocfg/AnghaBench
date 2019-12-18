#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* prev; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* next; } ;
typedef  TYPE_2__ STRING_T ;

/* Variables and functions */
 TYPE_2__* allocated_strings ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void free_string(const char *string)
{
    STRING_T *str;

    if (!string)
	return;

    str = (STRING_T *)(string - sizeof(STRING_T));
    if (str == allocated_strings)
    {
	allocated_strings = str->next;
	if (allocated_strings == str)
	    allocated_strings = NULL;
    }
    str->prev->next = str->next;
    str->next->prev = str->prev;
    free(str);
}