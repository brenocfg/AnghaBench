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
typedef  void u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int get_rloc_offs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *get_rloc_data(u32 *dl)
{
	return (u8 *)dl + get_rloc_offs(*dl);
}