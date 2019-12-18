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
struct TYPE_4__ {char* label; scalar_t__ kind; scalar_t__ newlabel; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ AST_GOTO ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  gotos ; 
 int /*<<< orphan*/  labels ; 
 scalar_t__ make_label () ; 
 TYPE_1__* map_get (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void backfill_labels() {
    for (int i = 0; i < vec_len(gotos); i++) {
        Node *src = vec_get(gotos, i);
        char *label = src->label;
        Node *dst = map_get(labels, label);
        if (!dst)
            error("stray %s: %s", src->kind == AST_GOTO ? "goto" : "unary &&", label);
        if (dst->newlabel)
            src->newlabel = dst->newlabel;
        else
            src->newlabel = dst->newlabel = make_label();
    }
}