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
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_keyword (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * lex () ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void expect(char id) {
    Token *tok = lex();
    if (!is_keyword(tok, id))
        errort(tok, "%c expected, but got %s", id, tok2s(tok));
}