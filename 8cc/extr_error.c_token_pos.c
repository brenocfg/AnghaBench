#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; TYPE_2__* file; } ;
typedef  TYPE_1__ Token ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 char* format (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *token_pos(Token *tok) {
    File *f = tok->file;
    if (!f)
        return "(unknown)";
    char *name = f->name ? f->name : "(unknown)";
    return format("%s:%d:%d", name, tok->line, tok->column);
}