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
 int /*<<< orphan*/  nv_rdport (void*,int,int) ; 
 int /*<<< orphan*/  nv_wrport (void*,int,int,int /*<<< orphan*/ ) ; 

u8
nv_rdvgac(void *obj, int head, u8 index)
{
	nv_wrport(obj, head, 0x03d4, index);
	return nv_rdport(obj, head, 0x03d5);
}