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
 int /*<<< orphan*/  br_range_enc32be (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_range_enc32le (unsigned char*,int /*<<< orphan*/ ,int) ; 

uint64_t
br_md5sha1_state(const br_md5sha1_context *cc, void *dst)
{
	unsigned char *out;

	out = dst;
	br_range_enc32le(out, cc->val_md5, 4);
	br_range_enc32be(out + 16, cc->val_sha1, 5);
	return cc->count;
}