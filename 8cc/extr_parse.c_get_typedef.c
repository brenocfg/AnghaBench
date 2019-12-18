#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_3__ {scalar_t__ kind; int /*<<< orphan*/ * ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ AST_TYPEDEF ; 
 int /*<<< orphan*/  env () ; 
 TYPE_1__* map_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Type *get_typedef(char *name) {
    Node *node = map_get(env(), name);
    return (node && node->kind == AST_TYPEDEF) ? node->ty : NULL;
}