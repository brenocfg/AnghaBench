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
struct yytbl_data {int td_lolen; int* td_data; } ;
typedef  int flex_int32_t ;
struct TYPE_2__ {int* dfaacc_set; int dfaacc_state; } ;

/* Variables and functions */
 int ABS (int /*<<< orphan*/ ) ; 
 int INT16_MAX ; 
 int JAMSTATE ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 scalar_t__ RULE_VARIABLE ; 
 int /*<<< orphan*/  YYTD_ID_ACCEPT ; 
 int /*<<< orphan*/  YYTD_ID_ACCLIST ; 
 int /*<<< orphan*/  YYTD_ID_BASE ; 
 int /*<<< orphan*/  YYTD_ID_CHK ; 
 int /*<<< orphan*/  YYTD_ID_DEF ; 
 int /*<<< orphan*/  YYTD_ID_META ; 
 int /*<<< orphan*/  YYTD_ID_NXT ; 
 int YY_TRAILING_HEAD_MASK ; 
 int YY_TRAILING_MASK ; 
 char* _ (char*) ; 
 int* accsiz ; 
 int* allocate_integer_array (int /*<<< orphan*/ ) ; 
 int* base ; 
 int /*<<< orphan*/  buf_prints (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int* chk ; 
 int /*<<< orphan*/  current_max_dfas ; 
 int /*<<< orphan*/  dataend () ; 
 int* def ; 
 TYPE_1__* dfaacc ; 
 size_t end_of_buffer_state ; 
 int /*<<< orphan*/  flex_free (void*) ; 
 int /*<<< orphan*/  flexerror (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genecs () ; 
 int /*<<< orphan*/  get_int16_decl () ; 
 int /*<<< orphan*/  get_int32_decl () ; 
 int jambase ; 
 int jamstate ; 
 int lastdfa ; 
 scalar_t__ long_align ; 
 int /*<<< orphan*/  mkdata (int) ; 
 struct yytbl_data* mkecstbl () ; 
 int /*<<< orphan*/  num_backing_up ; 
 int num_rules ; 
 int /*<<< orphan*/  numas ; 
 int numecs ; 
 scalar_t__ nummt ; 
 int numtemps ; 
 int* nxt ; 
 int /*<<< orphan*/  out_str_dec (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ reject ; 
 scalar_t__* rule_type ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tablesext ; 
 int /*<<< orphan*/  tableswr ; 
 int tblend ; 
 int /*<<< orphan*/ * tecbck ; 
 int /*<<< orphan*/  tmpuses ; 
 scalar_t__ trace ; 
 scalar_t__ useecs ; 
 scalar_t__ usemecs ; 
 scalar_t__ variable_trailing_context_rules ; 
 int /*<<< orphan*/  yydmap_buf ; 
 int /*<<< orphan*/  yytbl_data_compress (struct yytbl_data*) ; 
 int /*<<< orphan*/  yytbl_data_destroy (struct yytbl_data*) ; 
 scalar_t__ yytbl_data_fwrite (int /*<<< orphan*/ *,struct yytbl_data*) ; 
 int /*<<< orphan*/  yytbl_data_init (struct yytbl_data*,int /*<<< orphan*/ ) ; 

void gentabs ()
{
	int     i, j, k, *accset, nacc, *acc_array, total_states;
	int     end_of_buffer_action = num_rules + 1;
	struct yytbl_data *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
		*yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_data = 0, *yybase_data = 0, *yydef_data = 0,
		*yynxt_data = 0, *yychk_data = 0, *yyacclist_data=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++num_backing_up;

	if (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		int     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = end_of_buffer_action;
		accsiz[end_of_buffer_state] = 1;
		dfaacc[end_of_buffer_state].dfaacc_set =
			EOB_accepting_list;

		out_str_dec (long_align ? get_int32_decl () :
			     get_int16_decl (), "yy_acclist", MAX (numas,
								   1) + 1);
        
        buf_prints (&yydmap_buf,
                "\t{YYTD_ID_ACCLIST, (void**)&yy_acclist, sizeof(%s)},\n",
                long_align ? "flex_int32_t" : "flex_int16_t");

        yyacclist_tbl = (struct yytbl_data*)calloc(1,sizeof(struct yytbl_data));
        yytbl_data_init (yyacclist_tbl, YYTD_ID_ACCLIST);
        yyacclist_tbl->td_lolen  = MAX(numas,1) + 1;
        yyacclist_tbl->td_data = yyacclist_data = 
            (flex_int32_t *) calloc (yyacclist_tbl->td_lolen, sizeof (flex_int32_t));
        yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		for (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			if (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_set;
				nacc = accsiz[i];

				if (trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				for (k = 1; k <= nacc; ++k) {
					int     accnum = accset[k];

					++j;

					if (variable_trailing_context_rules
					    && !(accnum &
						 YY_TRAILING_HEAD_MASK)
					    && accnum > 0
					    && accnum <= num_rules
					    && rule_type[accnum] ==
					    RULE_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_MASK;
					}

					mkdata (accnum);
                    yyacclist_data[yyacclist_curr++] = accnum;

					if (trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						if (k < nacc)
							fputs (", ",
							       stderr);
						else
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend ();
        if (tablesext) {
            yytbl_data_compress (yyacclist_tbl);
            if (yytbl_data_fwrite (&tableswr, yyacclist_tbl) < 0)
                flexerror (_("Could not write yyacclist_tbl"));
            yytbl_data_destroy (yyacclist_tbl);
            yyacclist_tbl = NULL;
        }
	}

	else {
		dfaacc[end_of_buffer_state].dfaacc_state =
			end_of_buffer_action;

		for (i = 1; i <= lastdfa; ++i)
			acc_array[i] = dfaacc[i].dfaacc_state;

		/* add accepting number for jam state */
		acc_array[i] = 0;
	}

	/* Begin generating yy_accept */

	/* Spit out "yy_accept" array.  If we're doing "reject", it'll be
	 * pointers into the "yy_acclist" array.  Otherwise it's actual
	 * accepting numbers.  In either case, we just dump the numbers.
	 */

	/* "lastdfa + 2" is the size of "yy_accept"; includes room for C arrays
	 * beginning at 0 and for "jam" state.
	 */
	k = lastdfa + 2;

	if (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++k;

	out_str_dec (long_align ? get_int32_decl () : get_int16_decl (),
		     "yy_accept", k);

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_ACCEPT, (void**)&yy_accept, sizeof(%s)},\n",
		    long_align ? "flex_int32_t" : "flex_int16_t");

	yyacc_tbl =
		(struct yytbl_data *) calloc (1,
					      sizeof (struct yytbl_data));
	yytbl_data_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = k;
	yyacc_tbl->td_data = yyacc_data =
		(flex_int32_t *) calloc (yyacc_tbl->td_lolen, sizeof (flex_int32_t));
    yyacc_curr=1;

	for (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];

		if (!reject && trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_data[yyacc_curr++] = acc_array[i];

	if (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];
	}

	dataend ();
	if (tablesext) {
		yytbl_data_compress (yyacc_tbl);
		if (yytbl_data_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
		yytbl_data_destroy (yyacc_tbl);
		yyacc_tbl = NULL;
	}
	/* End generating yy_accept */

	if (useecs) {

		genecs ();
		if (tablesext) {
			struct yytbl_data *tbl;

			tbl = mkecstbl ();
			yytbl_data_compress (tbl);
			if (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;
		}
	}

	if (usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_data = 0;
		yymeta_tbl =
			(struct yytbl_data *) calloc (1,
						      sizeof (struct
							      yytbl_data));
		yytbl_data_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = numecs + 1;
		yymeta_tbl->td_data = yymecs_data =
			(flex_int32_t *) calloc (yymeta_tbl->td_lolen,
					    sizeof (flex_int32_t));

		if (trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);

		out_str_dec (get_int32_decl (), "yy_meta", numecs + 1);
		buf_prints (&yydmap_buf,
			    "\t{YYTD_ID_META, (void**)&yy_meta, sizeof(%s)},\n",
			    "flex_int32_t");

		for (i = 1; i <= numecs; ++i) {
			if (trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_data[i] = ABS (tecbck[i]);
		}

		dataend ();
		if (tablesext) {
			yytbl_data_compress (yymeta_tbl);
			if (yytbl_data_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_
					   ("Could not write yymeta_tbl"));
			yytbl_data_destroy (yymeta_tbl);
			yymeta_tbl = NULL;
		}
		/* End generating yy_meta */
	}

	total_states = lastdfa + numtemps;

	/* Begin generating yy_base */
	out_str_dec ((tblend >= INT16_MAX || long_align) ?
		     get_int32_decl () : get_int16_decl (),
		     "yy_base", total_states + 1);

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_BASE, (void**)&yy_base, sizeof(%s)},\n",
		    (tblend >= INT16_MAX
		     || long_align) ? "flex_int32_t" : "flex_int16_t");
	yybase_tbl =
		(struct yytbl_data *) calloc (1,
					      sizeof (struct yytbl_data));
	yytbl_data_init (yybase_tbl, YYTD_ID_BASE);
	yybase_tbl->td_lolen = total_states + 1;
	yybase_tbl->td_data = yybase_data =
		(flex_int32_t *) calloc (yybase_tbl->td_lolen,
				    sizeof (flex_int32_t));
	yybase_curr = 1;

	for (i = 1; i <= lastdfa; ++i) {
		int d = def[i];

		if (base[i] == JAMSTATE)
			base[i] = jambase;

		if (d == JAMSTATE)
			def[i] = jamstate;

		else if (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (base[i]);
		yybase_data[yybase_curr++] = base[i];
	}

	/* Generate jam state's base index. */
	mkdata (base[i]);
	yybase_data[yybase_curr++] = base[i];

	for (++i /* skip jam state */ ; i <= total_states; ++i) {
		mkdata (base[i]);
		yybase_data[yybase_curr++] = base[i];
		def[i] = jamstate;
	}

	dataend ();
	if (tablesext) {
		yytbl_data_compress (yybase_tbl);
		if (yytbl_data_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
		yytbl_data_destroy (yybase_tbl);
		yybase_tbl = NULL;
	}
	/* End generating yy_base */


	/* Begin generating yy_def */
	out_str_dec ((total_states >= INT16_MAX || long_align) ?
		     get_int32_decl () : get_int16_decl (),
		     "yy_def", total_states + 1);

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_DEF, (void**)&yy_def, sizeof(%s)},\n",
		    (total_states >= INT16_MAX
		     || long_align) ? "flex_int32_t" : "flex_int16_t");

	yydef_tbl =
		(struct yytbl_data *) calloc (1,
					      sizeof (struct yytbl_data));
	yytbl_data_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = total_states + 1;
	yydef_tbl->td_data = yydef_data =
		(flex_int32_t *) calloc (yydef_tbl->td_lolen, sizeof (flex_int32_t));

	for (i = 1; i <= total_states; ++i) {
		mkdata (def[i]);
		yydef_data[i] = def[i];
	}

	dataend ();
	if (tablesext) {
		yytbl_data_compress (yydef_tbl);
		if (yytbl_data_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
		yytbl_data_destroy (yydef_tbl);
		yydef_tbl = NULL;
	}
	/* End generating yy_def */


	/* Begin generating yy_nxt */
	out_str_dec ((total_states >= INT16_MAX || long_align) ?
		     get_int32_decl () : get_int16_decl (), "yy_nxt",
		     tblend + 1);

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_NXT, (void**)&yy_nxt, sizeof(%s)},\n",
		    (total_states >= INT16_MAX
		     || long_align) ? "flex_int32_t" : "flex_int16_t");

	yynxt_tbl =
		(struct yytbl_data *) calloc (1,
					      sizeof (struct yytbl_data));
	yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = tblend + 1;
	yynxt_tbl->td_data = yynxt_data =
		(flex_int32_t *) calloc (yynxt_tbl->td_lolen, sizeof (flex_int32_t));

	for (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		if (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_data[i] = nxt[i];
	}

	dataend ();
	if (tablesext) {
		yytbl_data_compress (yynxt_tbl);
		if (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
		yytbl_data_destroy (yynxt_tbl);
		yynxt_tbl = NULL;
	}
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	out_str_dec ((total_states >= INT16_MAX || long_align) ?
		     get_int32_decl () : get_int16_decl (), "yy_chk",
		     tblend + 1);

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_CHK, (void**)&yy_chk, sizeof(%s)},\n",
		    (total_states >= INT16_MAX
		     || long_align) ? "flex_int32_t" : "flex_int16_t");

	yychk_tbl =
		(struct yytbl_data *) calloc (1,
					      sizeof (struct yytbl_data));
	yytbl_data_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = tblend + 1;
	yychk_tbl->td_data = yychk_data =
		(flex_int32_t *) calloc (yychk_tbl->td_lolen, sizeof (flex_int32_t));

	for (i = 1; i <= tblend; ++i) {
		if (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_data[i] = chk[i];
	}

	dataend ();
	if (tablesext) {
		yytbl_data_compress (yychk_tbl);
		if (yytbl_data_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
		yytbl_data_destroy (yychk_tbl);
		yychk_tbl = NULL;
	}
	/* End generating yy_chk */

	flex_free ((void *) acc_array);
}