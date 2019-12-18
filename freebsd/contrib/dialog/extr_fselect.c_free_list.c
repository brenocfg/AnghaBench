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
struct TYPE_4__ {scalar_t__* data; int /*<<< orphan*/  mousex; int /*<<< orphan*/  win; int /*<<< orphan*/  par; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  init_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_list(LIST * list, int reinit)
{
    int n;

    if (list->data != 0) {
	for (n = 0; list->data[n] != 0; n++)
	    free(list->data[n]);
	free(list->data);
	list->data = 0;
    }
    if (reinit)
	init_list(list, list->par, list->win, list->mousex);
}