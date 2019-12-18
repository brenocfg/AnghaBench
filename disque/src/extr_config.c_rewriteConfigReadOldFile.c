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
struct rewriteConfigState {int has_tail; int /*<<< orphan*/ * lines; scalar_t__ numlines; void* rewritten; void* option_to_line; } ;
typedef  char* sds ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CONFIG_MAX_LINE ; 
 int /*<<< orphan*/  DISQUE_CONFIG_REWRITE_SIGNATURE ; 
 scalar_t__ ENOENT ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  optionSetDictType ; 
 int /*<<< orphan*/  optionToLineDictType ; 
 int /*<<< orphan*/  rewriteConfigAddLineNumberToOption (struct rewriteConfigState*,char*,int) ; 
 int /*<<< orphan*/  rewriteConfigAppendLine (struct rewriteConfigState*,char*) ; 
 char* sdscatsds (char*,char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 char* sdsnew (char*) ; 
 char** sdssplitargs (char*,int*) ; 
 int /*<<< orphan*/  sdstolower (char*) ; 
 char* sdstrim (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 struct rewriteConfigState* zmalloc (int) ; 

struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
    FILE *fp = fopen(path,"r");
    struct rewriteConfigState *state = zmalloc(sizeof(*state));
    char buf[CONFIG_MAX_LINE+1];
    int linenum = -1;

    if (fp == NULL && errno != ENOENT) return NULL;

    state->option_to_line = dictCreate(&optionToLineDictType,NULL);
    state->rewritten = dictCreate(&optionSetDictType,NULL);
    state->numlines = 0;
    state->lines = NULL;
    state->has_tail = 0;
    if (fp == NULL) return state;

    /* Read the old file line by line, populate the state. */
    while(fgets(buf,CONFIG_MAX_LINE+1,fp) != NULL) {
        int argc;
        sds *argv;
        sds line = sdstrim(sdsnew(buf),"\r\n\t ");

        linenum++; /* Zero based, so we init at -1 */

        /* Handle comments and empty lines. */
        if (line[0] == '#' || line[0] == '\0') {
            if (!state->has_tail && !strcmp(line,DISQUE_CONFIG_REWRITE_SIGNATURE))
                state->has_tail = 1;
            rewriteConfigAppendLine(state,line);
            continue;
        }

        /* Not a comment, split into arguments. */
        argv = sdssplitargs(line,&argc);
        if (argv == NULL) {
            /* Apparently the line is unparsable for some reason, for
             * instance it may have unbalanced quotes. Load it as a
             * comment. */
            sds aux = sdsnew("# ??? ");
            aux = sdscatsds(aux,line);
            sdsfree(line);
            rewriteConfigAppendLine(state,aux);
            continue;
        }

        sdstolower(argv[0]); /* We only want lowercase config directives. */

        /* Now we populate the state according to the content of this line.
         * Append the line and populate the option -> line numbers map. */
        rewriteConfigAppendLine(state,line);
        rewriteConfigAddLineNumberToOption(state,argv[0],linenum);

        sdsfreesplitres(argv,argc);
    }
    fclose(fp);
    return state;
}