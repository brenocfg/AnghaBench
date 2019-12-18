#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 int /*<<< orphan*/  expect_newline () ; 
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  map_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* read_ident () ; 

__attribute__((used)) static void read_undef() {
    Token *name = read_ident();
    expect_newline();
    map_remove(macros, name->sval);
}