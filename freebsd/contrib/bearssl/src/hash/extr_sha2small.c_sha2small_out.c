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
typedef  unsigned char uint32_t ;
struct TYPE_3__ {int count; int /*<<< orphan*/  val; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ br_sha224_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64be (unsigned char*,int) ; 
 int /*<<< orphan*/  br_range_enc32be (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  br_sha2small_round (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sha2small_out(const br_sha224_context *cc, void *dst, int num)
{
	unsigned char buf[64];
	uint32_t val[8];
	size_t ptr;

	ptr = (size_t)cc->count & 63;
	memcpy(buf, cc->buf, ptr);
	memcpy(val, cc->val, sizeof val);
	buf[ptr ++] = 0x80;
	if (ptr > 56) {
		memset(buf + ptr, 0, 64 - ptr);
		br_sha2small_round(buf, val);
		memset(buf, 0, 56);
	} else {
		memset(buf + ptr, 0, 56 - ptr);
	}
	br_enc64be(buf + 56, cc->count << 3);
	br_sha2small_round(buf, val);
	br_range_enc32be(dst, val, num);
}