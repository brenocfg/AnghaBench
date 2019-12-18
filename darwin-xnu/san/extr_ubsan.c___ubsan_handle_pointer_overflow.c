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
typedef  int /*<<< orphan*/  uint64_t ;
struct ubsan_violation {int /*<<< orphan*/ * member_4; struct ubsan_ptroverflow_desc* ptroverflow; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ubsan_ptroverflow_desc {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBSAN_POINTER_OVERFLOW ; 
 int /*<<< orphan*/  ubsan_handle (struct ubsan_violation*,int) ; 

void __ubsan_handle_pointer_overflow(struct ubsan_ptroverflow_desc *desc, uint64_t before, uint64_t after)
{
	struct ubsan_violation v = { UBSAN_POINTER_OVERFLOW, before, after, .ptroverflow = desc, &desc->loc };
	ubsan_handle(&v, false);
}