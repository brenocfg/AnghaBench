#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; int size; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 scalar_t__ KIND_BOOL ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  is_inttype (TYPE_1__*) ; 
 int /*<<< orphan*/ * peek () ; 
 int read_intexpr () ; 
 int /*<<< orphan*/  ty2s (TYPE_1__*) ; 

__attribute__((used)) static int read_bitsize(char *name, Type *ty) {
    if (!is_inttype(ty))
        error("non-integer type cannot be a bitfield: %s", ty2s(ty));
    Token *tok = peek();
    int r = read_intexpr();
    int maxsize = ty->kind == KIND_BOOL ? 1 : ty->size * 8;
    if (r < 0 || maxsize < r)
        errort(tok, "invalid bitfield size for %s: %d", ty2s(ty), r);
    if (r == 0 && name != NULL)
        errort(tok, "zero-width bitfield needs to be unnamed: %s", name);
    return r;
}