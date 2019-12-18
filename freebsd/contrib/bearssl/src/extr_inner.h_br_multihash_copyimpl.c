#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ impl; } ;
typedef  TYPE_1__ br_multihash_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 

__attribute__((used)) static inline void
br_multihash_copyimpl(br_multihash_context *dst,
	const br_multihash_context *src)
{
	memcpy((void *)dst->impl, src->impl, sizeof src->impl);
}