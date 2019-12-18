#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  column; int /*<<< orphan*/  line; TYPE_2__* file; int /*<<< orphan*/ * hideset; } ;
typedef  TYPE_1__ Token ;
struct TYPE_10__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_9__ {int /*<<< orphan*/  ntok; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 TYPE_2__* current_file () ; 
 TYPE_1__* malloc (int) ; 
 TYPE_3__ pos ; 

__attribute__((used)) static Token *make_token(Token *tmpl) {
    Token *r = malloc(sizeof(Token));
    *r = *tmpl;
    r->hideset = NULL;
    File *f = current_file();
    r->file = f;
    r->line = pos.line;
    r->column = pos.column;
    r->count = f->ntok++;
    return r;
}