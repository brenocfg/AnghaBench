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
typedef  int /*<<< orphan*/  v2_le ;
typedef  int /*<<< orphan*/  v1_le ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,void const*,int) ; 

__attribute__((used)) static int subtree_equal(void *context, const void *value1_le, const void *value2_le)
{
	__le64 v1_le, v2_le;
	memcpy(&v1_le, value1_le, sizeof(v1_le));
	memcpy(&v2_le, value2_le, sizeof(v2_le));

	return v1_le == v2_le;
}