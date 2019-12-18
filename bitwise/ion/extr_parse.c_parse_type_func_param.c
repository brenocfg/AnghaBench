#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Typespec ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 scalar_t__ TYPESPEC_NAME ; 
 int /*<<< orphan*/  error_here (char*) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_type () ; 

Typespec *parse_type_func_param(void) {
    Typespec *type = parse_type();
    if (match_token(TOKEN_COLON)) {
        if (type->kind != TYPESPEC_NAME) {
            error_here("Colons in parameters of func types must be preceded by names.");
        }
        type = parse_type();
    }
    return type;
}