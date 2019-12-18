#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rewriteConfigState {int has_tail; int /*<<< orphan*/ * lines; int /*<<< orphan*/  option_to_line; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 char const* DISQUE_CONFIG_REWRITE_SIGNATURE ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* listFirst (int /*<<< orphan*/ *) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewriteConfigAppendLine (struct rewriteConfigState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigMarkAsProcessed (struct rewriteConfigState*,char const*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char const*) ; 

void rewriteConfigRewriteLine(struct rewriteConfigState *state, const char *option, sds line, int force) {
    sds o = sdsnew(option);
    list *l = dictFetchValue(state->option_to_line,o);

    rewriteConfigMarkAsProcessed(state,option);

    if (!l && !force) {
        /* Option not used previously, and we are not forced to use it. */
        sdsfree(line);
        sdsfree(o);
        return;
    }

    if (l) {
        listNode *ln = listFirst(l);
        int linenum = (long) ln->value;

        /* There are still lines in the old configuration file we can reuse
         * for this option. Replace the line with the new one. */
        listDelNode(l,ln);
        if (listLength(l) == 0) dictDelete(state->option_to_line,o);
        sdsfree(state->lines[linenum]);
        state->lines[linenum] = line;
    } else {
        /* Append a new line. */
        if (!state->has_tail) {
            rewriteConfigAppendLine(state,
                sdsnew(DISQUE_CONFIG_REWRITE_SIGNATURE));
            state->has_tail = 1;
        }
        rewriteConfigAppendLine(state,line);
    }
    sdsfree(o);
}