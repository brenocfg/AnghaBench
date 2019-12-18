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
struct TYPE_2__ {int /*<<< orphan*/  level; int /*<<< orphan*/ * id; int /*<<< orphan*/  view; int /*<<< orphan*/  len; int /*<<< orphan*/  areas; int /*<<< orphan*/  pages; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int QETH_DBF_INFOS ; 
 int /*<<< orphan*/ * debug_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int debug_register_view (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* qeth_dbf ; 
 int /*<<< orphan*/  qeth_unregister_dbf_views () ; 

__attribute__((used)) static int qeth_register_dbf_views(void)
{
	int ret;
	int x;

	for (x = 0; x < QETH_DBF_INFOS; x++) {
		/* register the areas */
		qeth_dbf[x].id = debug_register(qeth_dbf[x].name,
						qeth_dbf[x].pages,
						qeth_dbf[x].areas,
						qeth_dbf[x].len);
		if (qeth_dbf[x].id == NULL) {
			qeth_unregister_dbf_views();
			return -ENOMEM;
		}

		/* register a view */
		ret = debug_register_view(qeth_dbf[x].id, qeth_dbf[x].view);
		if (ret) {
			qeth_unregister_dbf_views();
			return ret;
		}

		/* set a passing level */
		debug_set_level(qeth_dbf[x].id, qeth_dbf[x].level);
	}

	return 0;
}