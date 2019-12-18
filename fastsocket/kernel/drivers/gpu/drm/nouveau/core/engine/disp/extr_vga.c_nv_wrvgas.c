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

/* Variables and functions */
 int /*<<< orphan*/  nv_wrport (void*,int,int,int /*<<< orphan*/ ) ; 

void
nv_wrvgas(void *obj, int head, u8 index, u8 value)
{
	nv_wrport(obj, head, 0x03c4, index);
	nv_wrport(obj, head, 0x03c5, value);
}