#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error_here (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/  token_info () ; 
 int /*<<< orphan*/  token_kind_name (int /*<<< orphan*/ ) ; 

bool expect_token(TokenKind kind) {
    if (is_token(kind)) {
        next_token();
        return true;
    } else {
        fatal_error_here("Expected token %s, got %s", token_kind_name(kind), token_info());
        return false;
    }
}