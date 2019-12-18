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
struct xenbus_transaction {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  transaction_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XS_TRANSACTION_START ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 char* xs_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ xs_state ; 

int xenbus_transaction_start(struct xenbus_transaction *t)
{
	char *id_str;

	down_read(&xs_state.transaction_mutex);

	id_str = xs_single(XBT_NIL, XS_TRANSACTION_START, "", NULL);
	if (IS_ERR(id_str)) {
		up_read(&xs_state.transaction_mutex);
		return PTR_ERR(id_str);
	}

	t->id = simple_strtoul(id_str, NULL, 0);
	kfree(id_str);
	return 0;
}