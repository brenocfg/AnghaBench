#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ atEnd; int /*<<< orphan*/  isOpen; } ;
typedef  TYPE_1__* Lst ;
typedef  TYPE_1__* List ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ Head ; 
 int /*<<< orphan*/  LstValid (TYPE_1__*) ; 
 scalar_t__ Tail ; 

Boolean
Lst_IsAtEnd(Lst l)
{
    List list = l;

    return (!LstValid (l) || !list->isOpen ||
	    (list->atEnd == Head) || (list->atEnd == Tail));
}