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
struct yytbl_data {int td_lolen; int /*<<< orphan*/ * td_data; scalar_t__ td_hilen; int /*<<< orphan*/  td_flags; } ;
typedef  int /*<<< orphan*/  flex_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YYTD_DATA32 ; 
 int /*<<< orphan*/  YYTD_ID_EC ; 
 int /*<<< orphan*/  buf_prints (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int csize ; 
 int /*<<< orphan*/ * ecgroup ; 
 int /*<<< orphan*/  yydmap_buf ; 
 int /*<<< orphan*/  yytbl_data_init (struct yytbl_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct yytbl_data *mkecstbl (void)
{
	int i;
	struct yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = (struct yytbl_data *) calloc (1, sizeof (struct yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = csize;

	tbl->td_data = tdata =
		(flex_int32_t *) calloc (tbl->td_lolen, sizeof (flex_int32_t));

	for (i = 1; i < csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	buf_prints (&yydmap_buf,
		    "\t{YYTD_ID_EC, (void**)&yy_ec, sizeof(%s)},\n",
		    "flex_int32_t");

	return tbl;
}