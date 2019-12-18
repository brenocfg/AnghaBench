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
struct TYPE_6__ {scalar_t__ kind; int id; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 scalar_t__ TKEYWORD ; 
 TYPE_1__* copy_token (TYPE_1__*) ; 
 int /*<<< orphan*/  keywords ; 
 int /*<<< orphan*/  map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Token *maybe_convert_keyword(Token *tok) {
    if (tok->kind != TIDENT)
        return tok;
    int id = (intptr_t)map_get(keywords, tok->sval);
    if (!id)
        return tok;
    Token *r = copy_token(tok);
    r->kind = TKEYWORD;
    r->id = id;
    return r;
}