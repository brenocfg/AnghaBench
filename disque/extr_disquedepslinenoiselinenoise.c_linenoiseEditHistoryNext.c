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
struct linenoiseState {int history_index; char* buf; int buflen; int /*<<< orphan*/  pos; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int LINENOISE_HISTORY_PREV ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * history ; 
 int history_len ; 
 int /*<<< orphan*/  refreshLine (struct linenoiseState*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void linenoiseEditHistoryNext(struct linenoiseState *l, int dir) {
    if (history_len > 1) {
        /* Update the current history entry before to
         * overwrite it with the next one. */
        free(history[history_len - 1 - l->history_index]);
        history[history_len - 1 - l->history_index] = strdup(l->buf);
        /* Show the new entry */
        l->history_index += (dir == LINENOISE_HISTORY_PREV) ? 1 : -1;
        if (l->history_index < 0) {
            l->history_index = 0;
            return;
        } else if (l->history_index >= history_len) {
            l->history_index = history_len-1;
            return;
        }
        strncpy(l->buf,history[history_len - 1 - l->history_index],l->buflen);
        l->buf[l->buflen-1] = '\0';
        l->len = l->pos = strlen(l->buf);
        refreshLine(l);
    }
}