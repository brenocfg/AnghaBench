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
typedef  int /*<<< orphan*/  ushort_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_INFO_VLEN_V1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ushort_t
get_vlen_v1(ushort_t info)
{
	return (CTF_INFO_VLEN_V1(info));
}