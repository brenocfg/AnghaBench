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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t bytestream2_get_levarint(GetByteContext *gb)
{
    uint64_t val = 0;
    int shift = 0;
    int tmp;

    do {
        tmp = bytestream2_get_byte(gb);
        val |= (tmp & 127) << shift;
        shift += 7;
    } while (tmp & 128);

    return val;
}