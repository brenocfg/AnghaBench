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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  KeBugCheckEx (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Crush(UINT a, UINT b, UINT c, UINT d)
{
	KeBugCheckEx(0x3f000000 + a, (ULONG_PTR)a, (ULONG_PTR)b, (ULONG_PTR)c, (ULONG_PTR)d);
}