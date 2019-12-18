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
 scalar_t__ is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/ * read_decl_spec (int*) ; 
 int /*<<< orphan*/ * type_int ; 
 int /*<<< orphan*/  warnt (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Type *read_decl_spec_opt(int *sclass) {
    if (is_type(peek()))
        return read_decl_spec(sclass);
    warnt(peek(), "type specifier missing, assuming int");
    return type_int;
}