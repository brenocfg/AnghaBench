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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int /*<<< orphan*/ * read_abstract_declarator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_decl_spec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Type *read_cast_type() {
    return read_abstract_declarator(read_decl_spec(NULL));
}