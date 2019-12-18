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
struct TYPE_4__ {int /*<<< orphan*/  watching_ct; } ;
typedef  TYPE_1__ Tube ;
typedef  int /*<<< orphan*/  Ms ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  tube_dref (TYPE_1__*) ; 

__attribute__((used)) static void
on_ignore(Ms *a, Tube *t, size_t i)
{
    UNUSED_PARAMETER(a);
    UNUSED_PARAMETER(i);
    t->watching_ct--;
    tube_dref(t);
}