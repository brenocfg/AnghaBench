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
struct linenoiseState {size_t plen; char* buf; size_t len; size_t pos; size_t cols; char* prompt; } ;
struct abuf {int /*<<< orphan*/  len; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  abAppend (struct abuf*,char*,size_t) ; 
 int /*<<< orphan*/  abFree (struct abuf*) ; 
 int /*<<< orphan*/  abInit (struct abuf*) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refreshShowHints (struct abuf*,struct linenoiseState*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void refreshSingleLine(struct linenoiseState *l) {
    char seq[64];
    size_t plen = l->plen;
    char *buf = l->buf;
    size_t len = l->len;
    size_t pos = l->pos;
    struct abuf ab;

    while((plen+pos) >= l->cols) {
        buf++;
        len--;
        pos--;
    }
    while (plen+len > l->cols) {
        len--;
    }

    abInit(&ab);
    /* Cursor to left edge */
    snprintf(seq,64,"\r");
    abAppend(&ab,seq,strlen(seq));
    /* Write the prompt and the current buffer content */
    abAppend(&ab,l->prompt,strlen(l->prompt));
    abAppend(&ab,buf,len);
    /* Show hits if any. */
    refreshShowHints(&ab,l,plen);
    /* Erase to right */
    snprintf(seq,64,"\x1b[0K");
    abAppend(&ab,seq,strlen(seq));
    /* Move cursor to original position. */
    snprintf(seq,64,"\r\x1b[%dC", (int)(pos+plen));
    abAppend(&ab,seq,strlen(seq));
    if (fwrite(ab.b, ab.len, 1, stdout) == -1) {} /* Can't recover from write error. */
    abFree(&ab);
}