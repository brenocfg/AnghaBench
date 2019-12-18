#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p8; } ;
struct TYPE_5__ {int* buf; scalar_t__ capacity; TYPE_1__ internal_buf; scalar_t__* bytes; } ;
typedef  TYPE_2__ FLAC__MD5Context ;

/* Variables and functions */

void FLAC__MD5Init(FLAC__MD5Context *ctx)
{
	ctx->buf[0] = 0x67452301;
	ctx->buf[1] = 0xefcdab89;
	ctx->buf[2] = 0x98badcfe;
	ctx->buf[3] = 0x10325476;

	ctx->bytes[0] = 0;
	ctx->bytes[1] = 0;

	ctx->internal_buf.p8 = 0;
	ctx->capacity = 0;
}