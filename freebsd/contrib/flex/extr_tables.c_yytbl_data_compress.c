#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct yytbl_data {int td_flags; int /*<<< orphan*/  td_data; int /*<<< orphan*/  td_lolen; int /*<<< orphan*/  td_hilen; int /*<<< orphan*/  td_id; } ;
typedef  int flex_int32_t ;

/* Variables and functions */
 int BYTES2TFLAG (int) ; 
 int TFLAGS_CLRDATA (int) ; 
 scalar_t__ YYTDFLAGS2BYTES (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  flex_die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int min_int_size (struct yytbl_data*) ; 
 int yytbl_calc_total_len (struct yytbl_data*) ; 
 int yytbl_data_geti (struct yytbl_data*,int) ; 
 int /*<<< orphan*/  yytbl_data_init (struct yytbl_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yytbl_data_seti (struct yytbl_data*,int,int) ; 

void yytbl_data_compress (struct yytbl_data *tbl)
{
	flex_int32_t i, newsz, total_len;
	struct yytbl_data newtbl;

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);


	if (newsz == (int) YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		return;

	if (newsz > (int) YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		return;
	}

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = calloc (total_len, newsz);
	newtbl.td_flags =
		TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz);

	for (i = 0; i < total_len; i++) {
		flex_int32_t g;

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	free (tbl->td_data);
	*tbl = newtbl;
}