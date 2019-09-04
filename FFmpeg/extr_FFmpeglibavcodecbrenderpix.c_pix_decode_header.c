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
struct TYPE_3__ {void* height; void* width; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ PixHeader ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int pix_decode_header(PixHeader *out, GetByteContext *pgb)
{
    unsigned int header_len = bytestream2_get_be32(pgb);

    out->format = bytestream2_get_byte(pgb);
    bytestream2_skip(pgb, 2);
    out->width  = bytestream2_get_be16(pgb);
    out->height = bytestream2_get_be16(pgb);

    // the header is at least 11 bytes long; we read the first 7
    if (header_len < 11)
        return AVERROR_INVALIDDATA;

    // skip the rest of the header
    bytestream2_skip(pgb, header_len - 7);

    return 0;
}