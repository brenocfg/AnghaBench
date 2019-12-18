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
typedef  int /*<<< orphan*/  Vector ;

/* Variables and functions */
 int /*<<< orphan*/  emit_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_file_string (char*) ; 
 int /*<<< orphan*/ * read_toplevels () ; 
 int /*<<< orphan*/  stream_stash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_unstash () ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

void read_from_string(char *buf) {
    stream_stash(make_file_string(buf));
    Vector *toplevels = read_toplevels();
    for (int i = 0; i < vec_len(toplevels); i++)
        emit_toplevel(vec_get(toplevels, i));
    stream_unstash();
}