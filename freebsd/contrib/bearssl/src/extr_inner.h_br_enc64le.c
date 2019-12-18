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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int u; } ;
typedef  TYPE_1__ br_union_u64 ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc32le (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
br_enc64le(void *dst, uint64_t x)
{
#if BR_LE_UNALIGNED
	((br_union_u64 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = dst;
	br_enc32le(buf, (uint32_t)x);
	br_enc32le(buf + 4, (uint32_t)(x >> 32));
#endif
}