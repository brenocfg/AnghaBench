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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MAX_STRING_LENGTH ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

int get_word(char *word, FILE *fin) {
    int i = 0, ch;
    for ( ; ; ) {
        ch = fgetc(fin);
        if (ch == '\r') continue;
        if (i == 0 && ((ch == '\n') || (ch == EOF))) {
            word[i] = 0;
            return 1;
        }
        if (i == 0 && ((ch == ' ') || (ch == '\t'))) continue; // skip leading space
        if ((ch == EOF) || (ch == ' ') || (ch == '\t') || (ch == '\n')) {
            if (ch == '\n') ungetc(ch, fin); // return the newline next time as document ender
            break;
        }
        if (i < MAX_STRING_LENGTH - 1)
          word[i++] = ch; // don't allow words to exceed MAX_STRING_LENGTH
    }
    word[i] = 0; //null terminate
    // avoid truncation destroying a multibyte UTF-8 char except if only thing on line (so the i > x tests won't overwrite word[0])
    // see https://en.wikipedia.org/wiki/UTF-8#Description
    if (i == MAX_STRING_LENGTH - 1 && (word[i-1] & 0x80) == 0x80) {
        if ((word[i-1] & 0xC0) == 0xC0) {
            word[i-1] = '\0';
        } else if (i > 2 && (word[i-2] & 0xE0) == 0xE0) {
            word[i-2] = '\0';
        } else if (i > 3 && (word[i-3] & 0xF8) == 0xF0) {
            word[i-3] = '\0';
        }
    }
    return 0;
}