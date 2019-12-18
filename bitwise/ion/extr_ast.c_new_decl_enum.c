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
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_5__ {size_t num_items; int /*<<< orphan*/  items; int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {TYPE_1__ enum_decl; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  EnumItem ;
typedef  TYPE_2__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECL_ENUM ; 
 TYPE_2__* new_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

Decl *new_decl_enum(SrcPos pos, const char *name, Typespec *type, EnumItem *items, size_t num_items) {
    Decl *d = new_decl(DECL_ENUM, pos, name);
    d->enum_decl.type = type;
    d->enum_decl.items = AST_DUP(items);
    d->enum_decl.num_items = num_items;
    return d;
}