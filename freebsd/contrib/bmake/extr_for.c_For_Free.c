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
struct TYPE_4__ {struct TYPE_4__* parse_buf; int /*<<< orphan*/  items; int /*<<< orphan*/  vars; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ For ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strlist_clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
For_Free(For *arg)
{
    Buf_Destroy(&arg->buf, TRUE);
    strlist_clean(&arg->vars);
    strlist_clean(&arg->items);
    free(arg->parse_buf);

    free(arg);
}