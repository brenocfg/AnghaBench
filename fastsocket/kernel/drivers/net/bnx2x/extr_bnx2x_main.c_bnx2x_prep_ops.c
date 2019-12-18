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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct raw_op {int op; int offset; void* raw_data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void bnx2x_prep_ops(const u8 *_source, u8 *_target, u32 n)
{
	const __be32 *source = (const __be32 *)_source;
	struct raw_op *target = (struct raw_op *)_target;
	u32 i, j, tmp;

	for (i = 0, j = 0; i < n/8; i++, j += 2) {
		tmp = be32_to_cpu(source[j]);
		target[i].op = (tmp >> 24) & 0xff;
		target[i].offset = tmp & 0xffffff;
		target[i].raw_data = be32_to_cpu(source[j + 1]);
	}
}