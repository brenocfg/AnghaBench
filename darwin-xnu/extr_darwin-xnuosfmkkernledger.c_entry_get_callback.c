#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ledger_callback {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_2__* ledger_t ;
struct TYPE_8__ {TYPE_1__* lt_entries; } ;
struct TYPE_7__ {TYPE_4__* l_template; } ;
struct TYPE_6__ {struct ledger_callback* et_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEMPLATE_IDLE (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  TEMPLATE_INUSE (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static inline struct ledger_callback *
entry_get_callback(ledger_t ledger, int entry)
{
	struct ledger_callback *callback;
	spl_t s;

	TEMPLATE_INUSE(s, ledger->l_template);
	callback = ledger->l_template->lt_entries[entry].et_callback;
	TEMPLATE_IDLE(s, ledger->l_template);

	return (callback);
}