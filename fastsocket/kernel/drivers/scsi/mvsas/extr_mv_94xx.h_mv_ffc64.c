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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int mv_ffc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mv_ffc64(u64 v)
{
	int i;
	i = mv_ffc((u32)v);
	if (i >= 0)
		return i;
	i = mv_ffc((u32)(v>>32));

	if (i != 0)
		return 32 + i;

	return -1;
}