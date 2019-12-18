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
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/ * make_number (int /*<<< orphan*/ ) ; 
 int readc () ; 
 scalar_t__ strchr (char*,int) ; 
 int /*<<< orphan*/  unreadc (int) ; 

__attribute__((used)) static Token *read_number(char c) {
    Buffer *b = make_buffer();
    buf_write(b, c);
    char last = c;
    for (;;) {
        int c = readc();
        bool flonum = strchr("eEpP", last) && strchr("+-", c);
        if (!isdigit(c) && !isalpha(c) && c != '.' && !flonum) {
            unreadc(c);
            buf_write(b, '\0');
            return make_number(buf_body(b));
        }
        buf_write(b, c);
        last = c;
    }
}