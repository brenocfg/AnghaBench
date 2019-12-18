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
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * read_declarator_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_declarator_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Type *read_declarator_tail(Type *basety, Vector *params) {
    if (next_token('['))
        return read_declarator_array(basety);
    if (next_token('('))
        return read_declarator_func(basety, params);
    return basety;
}