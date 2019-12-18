#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ Token ;
struct TYPE_8__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ TINVALID ; 
 scalar_t__ TSTRING ; 
 int /*<<< orphan*/  concatenate_string (TYPE_1__*) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* peek () ; 
 TYPE_1__* read_token () ; 

__attribute__((used)) static Token *get() {
    Token *r = read_token();
    if (r->kind == TINVALID)
        errort(r, "stray character in program: '%c'", r->c);
    if (r->kind == TSTRING && peek()->kind == TSTRING)
        concatenate_string(r);
    return r;
}