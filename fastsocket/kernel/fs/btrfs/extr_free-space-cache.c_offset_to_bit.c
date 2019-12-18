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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long offset_to_bit(u64 bitmap_start, u32 unit,
					  u64 offset)
{
	BUG_ON(offset < bitmap_start);
	offset -= bitmap_start;
	return (unsigned long)(div_u64(offset, unit));
}