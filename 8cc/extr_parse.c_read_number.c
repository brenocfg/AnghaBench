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
struct TYPE_5__ {char* sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * read_float (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_int (TYPE_1__*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 scalar_t__ strpbrk (char*,char*) ; 

__attribute__((used)) static Node *read_number(Token *tok) {
    char *s = tok->sval;
    bool isfloat = strpbrk(s, ".pP") || (strncasecmp(s, "0x", 2) && strpbrk(s, "eE"));
    return isfloat ? read_float(tok) : read_int(tok);
}