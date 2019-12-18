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
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {char* sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ LONG_MAX ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/ * ast_inttype (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,char,char*) ; 
 int /*<<< orphan*/ * read_int_suffix (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/ * type_int ; 
 int /*<<< orphan*/ * type_long ; 
 int /*<<< orphan*/ * type_uint ; 
 int /*<<< orphan*/ * type_ulong ; 

__attribute__((used)) static Node *read_int(Token *tok) {
    char *s = tok->sval;
    char *end;
    long v = !strncasecmp(s, "0b", 2)
        ? strtoul(s + 2, &end, 2) : strtoul(s, &end, 0);
    Type *ty = read_int_suffix(end);
    if (ty)
        return ast_inttype(ty, v);
    if (*end != '\0')
        errort(tok, "invalid character '%c': %s", *end, s);

    // C11 6.4.4.1p5: Decimal constant type is int, long, or long long.
    // In 8cc, long and long long are the same size.
    bool base10 = (*s != '0');
    if (base10) {
        ty = !(v & ~(long)INT_MAX) ? type_int : type_long;
        return ast_inttype(ty, v);
    }
    // Octal or hexadecimal constant type may be unsigned.
    ty = !(v & ~(unsigned long)INT_MAX) ? type_int
        : !(v & ~(unsigned long)UINT_MAX) ? type_uint
        : !(v & ~(unsigned long)LONG_MAX) ? type_long
        : type_ulong;
    return ast_inttype(ty, v);
}