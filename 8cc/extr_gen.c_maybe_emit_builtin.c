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
struct TYPE_6__ {int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_builtin_reg_class (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_builtin_return_address (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_builtin_va_start (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool maybe_emit_builtin(Node *node) {
    SAVE;
    if (!strcmp("__builtin_return_address", node->fname)) {
        emit_builtin_return_address(node);
        return true;
    }
    if (!strcmp("__builtin_reg_class", node->fname)) {
        emit_builtin_reg_class(node);
        return true;
    }
    if (!strcmp("__builtin_va_start", node->fname)) {
        emit_builtin_va_start(node);
        return true;
    }
    return false;
}