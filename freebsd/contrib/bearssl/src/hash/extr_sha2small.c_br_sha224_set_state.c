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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ br_sha224_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_range_dec32be (int /*<<< orphan*/ ,int,void const*) ; 

void
br_sha224_set_state(br_sha224_context *cc, const void *stb, uint64_t count)
{
	br_range_dec32be(cc->val, 8, stb);
	cc->count = count;
}