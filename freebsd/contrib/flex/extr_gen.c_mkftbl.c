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
struct yytbl_data {int td_lolen; int* td_data; scalar_t__ td_hilen; int /*<<< orphan*/  td_flags; } ;
typedef  int flex_int32_t ;
struct TYPE_2__ {int dfaacc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  YYTD_DATA32 ; 
 int /*<<< orphan*/  YYTD_ID_ACCEPT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  buf_prints (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__* dfaacc ; 
 size_t end_of_buffer_state ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int lastdfa ; 
 scalar_t__ long_align ; 
 int num_rules ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ trace ; 
 int /*<<< orphan*/  yydmap_buf ; 
 int /*<<< orphan*/  yytbl_data_init (struct yytbl_data*,int /*<<< orphan*/ ) ; 

struct yytbl_data *mkftbl (void)
{
	int i;
	int     end_of_buffer_action = num_rules + 1;
	struct yytbl_data *tbl;
	flex_int32_t *tdata = 0;

	tbl = (struct yytbl_data *) calloc (1, sizeof (struct yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = lastdfa + 1;

	tbl->td_data = tdata =
		(flex_int32_t *) calloc (tbl->td_lolen, sizeof (flex_int32_t));

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	for (i = 1; i <= lastdfa; ++i) {
		int anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		if (trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_ACCEPT, (void**)&yy_accept, sizeof(%s)},\n",
		    long_align ? "flex_int32_t" : "flex_int16_t");
	return tbl;
}