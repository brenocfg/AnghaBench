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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  node2s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void a2s_declinit(Buffer *b, Vector *initlist) {
    for (int i = 0; i < vec_len(initlist); i++) {
        if (i > 0)
            buf_printf(b, " ");
        Node *init = vec_get(initlist, i);
        buf_printf(b, "%s", node2s(init));
    }
}