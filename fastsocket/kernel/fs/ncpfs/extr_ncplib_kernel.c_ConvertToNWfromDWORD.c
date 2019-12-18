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
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 

__attribute__((used)) static inline void ConvertToNWfromDWORD(__u16 v0, __u16 v1, __u8 ret[6])
{
	__le16 *dest = (__le16 *) ret;
	dest[1] = cpu_to_le16(v0);
	dest[2] = cpu_to_le16(v1);
	dest[0] = cpu_to_le16(v0 + 1);
	return;
}