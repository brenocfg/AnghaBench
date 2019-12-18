#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_conv (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ is_flotype (int /*<<< orphan*/ ) ; 
 TYPE_1__* read_expr () ; 
 int /*<<< orphan*/  type_bool ; 

__attribute__((used)) static Node *read_boolean_expr() {
    Node *cond = read_expr();
    return is_flotype(cond->ty) ? ast_conv(type_bool, cond) : cond;
}