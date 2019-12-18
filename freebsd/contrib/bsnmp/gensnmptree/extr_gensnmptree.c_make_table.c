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
struct node {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  PREFIX_LEN ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* file_prefix ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gen_enums (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_header (int /*<<< orphan*/ *,struct node const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_table (int /*<<< orphan*/ *,struct node const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int tree_size ; 

__attribute__((used)) static void
make_table(const struct node *root, int gen_funcs)
{
	FILE *fp;

	char fname[MAXPATHLEN + 1];
	sprintf(fname, "%stree.h", file_prefix);
	if ((fp = fopen(fname, "w")) == NULL)
		err(1, "%s: ", fname);
	gen_header(fp, root, PREFIX_LEN, NULL);

	fprintf(fp, "\n#ifdef SNMPTREE_TYPES\n");
	gen_enums(fp, gen_funcs);
	fprintf(fp, "\n#endif /* SNMPTREE_TYPES */\n\n");

	fprintf(fp, "#define %sCTREE_SIZE %u\n", file_prefix, tree_size);
	fprintf(fp, "extern const struct snmp_node %sctree[];\n", file_prefix);

	fclose(fp);

	sprintf(fname, "%stree.c", file_prefix);
	if ((fp = fopen(fname, "w")) == NULL)
		err(1, "%s: ", fname);
	gen_table(fp, root);
	fclose(fp);
}