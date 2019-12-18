#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* datum; } ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__* ListNode ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 TYPE_1__* Lst_First (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Remove (int /*<<< orphan*/ ,TYPE_1__*) ; 

void *
Lst_DeQueue(Lst l)
{
    void *rd;
    ListNode	tln;

    tln = Lst_First(l);
    if (tln == NULL) {
	return NULL;
    }

    rd = tln->datum;
    if (Lst_Remove(l, tln) == FAILURE) {
	return NULL;
    } else {
	return (rd);
    }
}