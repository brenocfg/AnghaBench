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
 int /*<<< orphan*/  buffers ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  make_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  make_vector () ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stream_push (int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lex_init(char *filename) {
    vec_push(buffers, make_vector());
    if (!strcmp(filename, "-")) {
        stream_push(make_file(stdin, "-"));
        return;
    }
    FILE *fp = fopen(filename, "r");
    if (!fp)
        error("Cannot open %s: %s", filename, strerror(errno));
    stream_push(make_file(fp, filename));
}