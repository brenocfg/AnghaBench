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
struct TYPE_4__ {char* sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_floattype (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,char,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 double strtod (char*,char**) ; 
 int /*<<< orphan*/  type_double ; 
 int /*<<< orphan*/  type_float ; 
 int /*<<< orphan*/  type_ldouble ; 

__attribute__((used)) static Node *read_float(Token *tok) {
    char *s = tok->sval;
    char *end;
    double v = strtod(s, &end);
    // C11 6.4.4.2p4: The default type for flonum is double.
    if (!strcasecmp(end, "l"))
        return ast_floattype(type_ldouble, v);
    if (!strcasecmp(end, "f"))
        return ast_floattype(type_float, v);
    if (*end != '\0')
        errort(tok, "invalid character '%c': %s", *end, s);
    return ast_floattype(type_double, v);
}