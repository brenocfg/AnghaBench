#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double f64; int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ av_alias64 ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le64 (int /*<<< orphan*/ *) ; 

double ff_tget_double(GetByteContext *gb, int le)
{
    av_alias64 i = { .u64 = le ? bytestream2_get_le64(gb) : bytestream2_get_be64(gb)};
    return i.f64;
}