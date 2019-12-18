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
struct TYPE_4__ {int /*<<< orphan*/  notes; } ;
typedef  int /*<<< orphan*/  Notes ;
typedef  TYPE_1__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error_here (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_decl_opt () ; 
 int /*<<< orphan*/  parse_notes () ; 
 int /*<<< orphan*/  token_info () ; 

Decl *parse_decl(void) {
    Notes notes = parse_notes();
    Decl *decl = parse_decl_opt();
    if (!decl) {
        fatal_error_here("Expected declaration keyword, got %s", token_info());
    }
    decl->notes = notes;
    return decl;
}