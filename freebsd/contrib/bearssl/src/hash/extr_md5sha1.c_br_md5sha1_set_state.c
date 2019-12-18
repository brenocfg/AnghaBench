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
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  val_sha1; int /*<<< orphan*/  val_md5; } ;
typedef  TYPE_1__ br_md5sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_range_dec32be (int /*<<< orphan*/ ,int,unsigned char const*) ; 
 int /*<<< orphan*/  br_range_dec32le (int /*<<< orphan*/ ,int,unsigned char const*) ; 

void
br_md5sha1_set_state(br_md5sha1_context *cc, const void *stb, uint64_t count)
{
	const unsigned char *buf;

	buf = stb;
	br_range_dec32le(cc->val_md5, 4, buf);
	br_range_dec32be(cc->val_sha1, 5, buf + 16);
	cc->count = count;
}