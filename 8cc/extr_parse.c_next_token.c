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
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool next_token(int kind) {
    Token *tok = get();
    if (is_keyword(tok, kind))
        return true;
    unget_token(tok);
    return false;
}