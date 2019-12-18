#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ Pos ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 TYPE_2__* current_file () ; 
 char* format (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *pos_string(Pos *p) {
    File *f = current_file();
    return format("%s:%d:%d", f ? f->name : "(unknown)", p->line, p->column);
}