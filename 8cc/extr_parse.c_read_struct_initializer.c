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
 int /*<<< orphan*/  read_struct_initializer_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sort_inits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_struct_initializer(Vector *inits, Type *ty, int off, bool designated) {
    read_struct_initializer_sub(inits, ty, off, designated);
    sort_inits(inits);
}