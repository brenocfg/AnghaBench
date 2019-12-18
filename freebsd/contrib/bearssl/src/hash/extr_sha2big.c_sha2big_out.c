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
typedef  unsigned char uint64_t ;
struct TYPE_3__ {int count; int /*<<< orphan*/  val; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ br_sha384_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64be (unsigned char*,int) ; 
 int /*<<< orphan*/  br_range_enc64be (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha2big_round (unsigned char*,unsigned char*) ; 

__attribute__((used)) static void
sha2big_out(const br_sha384_context *cc, void *dst, int num)
{
	unsigned char buf[128];
	uint64_t val[8];
	size_t ptr;

	ptr = (size_t)cc->count & 127;
	memcpy(buf, cc->buf, ptr);
	memcpy(val, cc->val, sizeof val);
	buf[ptr ++] = 0x80;
	if (ptr > 112) {
		memset(buf + ptr, 0, 128 - ptr);
		sha2big_round(buf, val);
		memset(buf, 0, 112);
	} else {
		memset(buf + ptr, 0, 112 - ptr);
	}
	br_enc64be(buf + 112, cc->count >> 61);
	br_enc64be(buf + 120, cc->count << 3);
	sha2big_round(buf, val);
	br_range_enc64be(dst, val, num);
}