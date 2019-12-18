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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  val; scalar_t__ buf; scalar_t__ count; } ;
typedef  TYPE_1__ br_md5_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_md5_round (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,size_t) ; 

void
br_md5_update(br_md5_context *cc, const void *data, size_t len)
{
	const unsigned char *buf;
	size_t ptr;

	buf = data;
	ptr = (size_t)cc->count & 63;
	while (len > 0) {
		size_t clen;

		clen = 64 - ptr;
		if (clen > len) {
			clen = len;
		}
		memcpy(cc->buf + ptr, buf, clen);
		ptr += clen;
		buf += clen;
		len -= clen;
		cc->count += (uint64_t)clen;
		if (ptr == 64) {
			br_md5_round(cc->buf, cc->val);
			ptr = 0;
		}
	}
}