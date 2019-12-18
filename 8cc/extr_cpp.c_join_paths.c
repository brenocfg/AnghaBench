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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 char* buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *join_paths(Vector *args) {
    Buffer *b = make_buffer();
    for (int i = 0; i < vec_len(args); i++)
        buf_printf(b, "%s", tok2s(vec_get(args, i)));
    return buf_body(b);
}