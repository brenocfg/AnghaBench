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
typedef  int /*<<< orphan*/  u32 ;
struct nes_v4_quad {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32c (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static inline __le32 get_crc_value(struct nes_v4_quad *nes_quad)
{
	u32 crc_value;
	crc_value = crc32c(~0, (void *)nes_quad, sizeof (struct nes_v4_quad));

	/*
	 * With commit ef19454b ("[LIB] crc32c: Keep intermediate crc
	 * state in cpu order"), behavior of crc32c changes on
	 * big-endian platforms.  Our algorithm expects the previous
	 * behavior; otherwise we have RDMA connection establishment
	 * issue on big-endian.
	 */
	return cpu_to_le32(crc_value);
}