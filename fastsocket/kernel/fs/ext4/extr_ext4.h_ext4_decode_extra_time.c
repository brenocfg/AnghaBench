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
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int __u64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EXT4_EPOCH_BITS ; 
 int EXT4_EPOCH_MASK ; 
 int EXT4_NSEC_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ext4_decode_extra_time(struct timespec *time, __le32 extra)
{
       if (sizeof(time->tv_sec) > 4)
	       time->tv_sec |= (__u64)(le32_to_cpu(extra) & EXT4_EPOCH_MASK)
			       << 32;
       time->tv_nsec = (le32_to_cpu(extra) & EXT4_NSEC_MASK) >> EXT4_EPOCH_BITS;
}