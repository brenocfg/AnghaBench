#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_RBRACE ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_typespec_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_type () ; 
 TYPE_1__ token ; 

Typespec *parse_type_tuple(void) {
    SrcPos pos = token.pos;
    Typespec **fields = NULL;
    while (!is_token(TOKEN_RBRACE)) {
        Typespec *field = parse_type();
        buf_push(fields, field);
        if (!match_token(TOKEN_COMMA)) {
            break;
        }
    }
    expect_token(TOKEN_RBRACE);
    return new_typespec_tuple(pos, fields, buf_len(fields));
}