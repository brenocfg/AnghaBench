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
 int /*<<< orphan*/  TNUMBER ; 
 int /*<<< orphan*/  format (char*,scalar_t__) ; 
 int /*<<< orphan*/  make_token_pushback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stream_depth () ; 

__attribute__((used)) static void handle_include_level_macro(Token *tmpl) {
    make_token_pushback(tmpl, TNUMBER, format("%d", stream_depth() - 1));
}