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
struct str {int nfields; char* tag; struct field* field; } ;
struct field {int type; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  T_INT 132 
#define  T_NODE 131 
#define  T_NODELIST 130 
#define  T_OTHER 129 
#define  T_STRING 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  indent (int,int /*<<< orphan*/ *) ; 
 char** nodename ; 
 struct str** nodestr ; 
 size_t nstr ; 
 int ntypes ; 
 struct str* str ; 

__attribute__((used)) static void
outfunc(FILE *cfile, int calcsize)
{
	struct str *sp;
	struct field *fp;
	int i;

	fputs("      if (n == NULL)\n", cfile);
	if (calcsize)
		fputs("	    return;\n", cfile);
	else
		fputs("	    return NULL;\n", cfile);
	if (calcsize)
		fputs("      result->blocksize += nodesize[n->type];\n", cfile);
	else {
		fputs("      new = state->block;\n", cfile);
		fputs("      state->block = (char *)state->block + nodesize[n->type];\n", cfile);
	}
	fputs("      switch (n->type) {\n", cfile);
	for (sp = str ; sp < &str[nstr] ; sp++) {
		for (i = 0 ; i < ntypes ; i++) {
			if (nodestr[i] == sp)
				fprintf(cfile, "      case %s:\n", nodename[i]);
		}
		for (i = sp->nfields ; --i >= 1 ; ) {
			fp = &sp->field[i];
			switch (fp->type) {
			case T_NODE:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "calcsize(n->%s.%s, result);\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = copynode(n->%s.%s, state);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_NODELIST:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "sizenodelist(n->%s.%s, result);\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = copynodelist(n->%s.%s, state);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_STRING:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "result->stringsize += strlen(n->%s.%s) + 1;\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = nodesavestr(n->%s.%s, state);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_INT:
			case T_OTHER:
				if (! calcsize) {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = n->%s.%s;\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			}
		}
		indent(12, cfile);
		fputs("break;\n", cfile);
	}
	fputs("      };\n", cfile);
	if (! calcsize)
		fputs("      new->type = n->type;\n", cfile);
}