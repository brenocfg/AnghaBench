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
struct TYPE_5__ {int /*<<< orphan*/  td_labels; } ;
typedef  TYPE_1__ tdata_t ;
struct TYPE_6__ {int le_idx; char* le_name; } ;
typedef  TYPE_2__ labelent_t ;

/* Variables and functions */
 scalar_t__ list_find (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_first (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char*,char*) ; 
 int /*<<< orphan*/  tdata_label_find_cb ; 

int
tdata_label_find(tdata_t *td, char *label)
{
	labelent_t let;
	labelent_t *ret;

	if (streq(label, "BASE")) {
		ret = (labelent_t *)list_first(td->td_labels);
		return (ret ? ret->le_idx : -1);
	}

	let.le_name = label;

	if (!(ret = (labelent_t *)list_find(td->td_labels, &let,
	    tdata_label_find_cb)))
		return (-1);

	return (ret->le_idx);
}