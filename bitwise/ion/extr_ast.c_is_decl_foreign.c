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
typedef  int /*<<< orphan*/  Decl ;

/* Variables and functions */
 int /*<<< orphan*/  foreign_name ; 
 int /*<<< orphan*/ * get_decl_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool is_decl_foreign(Decl *decl) {
    return decl && get_decl_note(decl, foreign_name) != NULL;
}