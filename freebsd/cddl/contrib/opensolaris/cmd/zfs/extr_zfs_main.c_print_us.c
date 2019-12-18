#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_t ;
struct TYPE_6__ {int /*<<< orphan*/  usn_nvl; } ;
typedef  TYPE_1__ us_node_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int USFIELD_LAST ; 
 int USFIELD_NAME ; 
 int USFIELD_TYPE ; 
 char* gettext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_us_node (scalar_t__,scalar_t__,int*,int,size_t*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * us_field_hdr ; 
 TYPE_1__* uu_avl_first (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_next (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
print_us(boolean_t scripted, boolean_t parsable, int *fields, int types,
    size_t *width, boolean_t rmnode, uu_avl_t *avl)
{
	us_node_t *node;
	const char *col;
	int cfield = 0;
	int field;

	if (!scripted) {
		boolean_t first = B_TRUE;

		while ((field = fields[cfield]) != USFIELD_LAST) {
			col = gettext(us_field_hdr[field]);
			if (field == USFIELD_TYPE || field == USFIELD_NAME) {
				(void) printf(first ? "%-*s" : "  %-*s",
				    width[field], col);
			} else {
				(void) printf(first ? "%*s" : "  %*s",
				    width[field], col);
			}
			first = B_FALSE;
			cfield++;
		}
		(void) printf("\n");
	}

	for (node = uu_avl_first(avl); node; node = uu_avl_next(avl, node)) {
		print_us_node(scripted, parsable, fields, types, width, node);
		if (rmnode)
			nvlist_free(node->usn_nvl);
	}
}