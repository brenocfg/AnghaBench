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
struct TYPE_5__ {int is_relative; size_t num_names; int import_all; size_t num_items; void* items; void* names; } ;
struct TYPE_6__ {char const* name; TYPE_1__ import; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  char const* ImportItem ;
typedef  TYPE_2__ Decl ;

/* Variables and functions */
 void* AST_DUP (char const**) ; 
 int /*<<< orphan*/  DECL_IMPORT ; 
 TYPE_2__* new_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Decl *new_decl_import(SrcPos pos, const char *rename_name, bool is_relative, const char **names, size_t num_names, bool import_all, ImportItem *items, size_t num_items) {
    Decl *d = new_decl(DECL_IMPORT, pos, NULL);
    d->name = rename_name;
    d->import.is_relative = is_relative;
    d->import.names = AST_DUP(names);
    d->import.num_names = num_names;
    d->import.import_all = import_all;
    d->import.items = AST_DUP(items);
    d->import.num_items = num_items;
    return d;
}