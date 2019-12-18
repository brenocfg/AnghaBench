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
typedef  int /*<<< orphan*/  HT ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  HT_clear (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  HT_free (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 void* HT_new () ; 
 int /*<<< orphan*/ * all_chains ; 
 scalar_t__ all_chains_len ; 
 scalar_t__ all_chains_ptr ; 
 int /*<<< orphan*/  conf_close () ; 
 int /*<<< orphan*/  conf_init (char const*) ; 
 scalar_t__ conf_next_line () ; 
 long current_linenum ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 void* keys ; 
 char* parse_header_name () ; 
 scalar_t__ parse_keyvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_object (char*,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  stderr ; 
 void* trust_anchors ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
process_conf_file(const char *fname)
{
	char *objtype;
	HT *objdata;
	long objlinenum;

	keys = HT_new();
	trust_anchors = HT_new();
	all_chains = NULL;
	all_chains_ptr = 0;
	all_chains_len = 0;
	conf_init(fname);
	objtype = NULL;
	objdata = HT_new();
	objlinenum = 0;
	for (;;) {
		char *hname;

		if (conf_next_line() < 0) {
			break;
		}
		hname = parse_header_name();
		if (hname != NULL) {
			if (objtype != NULL) {
				parse_object(objtype, objdata, objlinenum);
				HT_clear(objdata, xfree);
				xfree(objtype);
			}
			objtype = hname;
			objlinenum = current_linenum;
			continue;
		}
		if (objtype == NULL) {
			fprintf(stderr, "no current section (line %ld)\n",
				current_linenum);
			exit(EXIT_FAILURE);
		}
		if (parse_keyvalue(objdata) < 0) {
			fprintf(stderr, "wrong configuration, line %ld\n",
				current_linenum);
			exit(EXIT_FAILURE);
		}
	}
	if (objtype != NULL) {
		parse_object(objtype, objdata, objlinenum);
		xfree(objtype);
	}
	HT_free(objdata, xfree);
	conf_close();
}