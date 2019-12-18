#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* declvar; int /*<<< orphan*/  declinit; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  isstatic; } ;
struct TYPE_5__ {TYPE_2__* ty; int /*<<< orphan*/  glabel; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  do_emit_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit (char*,int) ; 
 int /*<<< orphan*/  emit_noindent (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_data(Node *v, int off, int depth) {
    SAVE;
    emit(".data %d", depth);
    if (!v->declvar->ty->isstatic)
        emit_noindent(".global %s", v->declvar->glabel);
    emit_noindent("%s:", v->declvar->glabel);
    do_emit_data(v->declinit, v->declvar->ty->size, off, depth);
}