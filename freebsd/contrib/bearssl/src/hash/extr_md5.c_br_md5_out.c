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
typedef  TYPE_1__ br_md5_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64le (unsigned char*,int) ; 
 int /*<<< orphan*/  br_md5_round (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  br_range_enc32le (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
br_md5_out(const br_md5_context *cc, void *dst)
{
	unsigned char buf[64];
	uint32_t val[4];
	size_t ptr;

	ptr = (size_t)cc->count & 63;
	memcpy(buf, cc->buf, ptr);
	memcpy(val, cc->val, sizeof val);
	buf[ptr ++] = 0x80;
	if (ptr > 56) {
		memset(buf + ptr, 0, 64 - ptr);
		br_md5_round(buf, val);
		memset(buf, 0, 56);
	} else {
		memset(buf + ptr, 0, 56 - ptr);
	}
	br_enc64le(buf + 56, cc->count << 3);
	br_md5_round(buf, val);
	br_range_enc32le(dst, val, 4);
}