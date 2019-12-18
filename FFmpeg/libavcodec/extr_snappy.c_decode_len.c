#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ AVERROR_INVALIDDATA ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ bytestream2_get_levarint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t decode_len(GetByteContext *gb)
{
    int64_t len = bytestream2_get_levarint(gb);

    if (len < 0 || len > UINT_MAX)
        return AVERROR_INVALIDDATA;

    return len;
}