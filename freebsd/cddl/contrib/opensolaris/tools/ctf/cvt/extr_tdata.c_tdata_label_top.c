#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  td_labels; } ;
typedef  TYPE_1__ tdata_t ;
typedef  int /*<<< orphan*/  labelent_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdata_label_top_cb ; 

labelent_t *
tdata_label_top(tdata_t *td)
{
	labelent_t *top = NULL;

	(void) list_iter(td->td_labels, tdata_label_top_cb, &top);

	return (top);
}