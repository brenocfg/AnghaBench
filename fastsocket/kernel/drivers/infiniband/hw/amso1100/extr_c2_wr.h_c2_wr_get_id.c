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
struct c2wr_hdr {int /*<<< orphan*/  id; } ;

/* Variables and functions */

__attribute__((used)) static __inline__ u8 c2_wr_get_id(void *wr)
{
	return ((struct c2wr_hdr *) wr)->id;
}