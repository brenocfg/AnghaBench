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
 int /*<<< orphan*/  br_range_enc32be (void*,int /*<<< orphan*/ ,int) ; 

uint64_t
br_sha224_state(const br_sha224_context *cc, void *dst)
{
	br_range_enc32be(dst, cc->val, 8);
	return cc->count;
}