#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  line; TYPE_1__* file; } ;
typedef  TYPE_2__ Token ;
struct TYPE_8__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SourceLoc ;

/* Variables and functions */
 TYPE_3__* malloc (int) ; 
 TYPE_2__* peek () ; 
 TYPE_3__* source_loc ; 

__attribute__((used)) static void mark_location() {
    Token *tok = peek();
    source_loc = malloc(sizeof(SourceLoc));
    source_loc->file = tok->file->name;
    source_loc->line = tok->line;
}