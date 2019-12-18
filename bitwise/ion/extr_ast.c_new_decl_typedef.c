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
struct TYPE_5__ {int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {TYPE_1__ typedef_decl; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_TYPEDEF ; 
 TYPE_2__* new_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

Decl *new_decl_typedef(SrcPos pos, const char *name, Typespec *type) {
    Decl *d = new_decl(DECL_TYPEDEF, pos, name);
    d->typedef_decl.type = type;
    return d;
}