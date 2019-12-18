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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EXT4_EPOCH_BITS ; 
 int EXT4_EPOCH_MASK ; 
 int EXT4_NSEC_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline __le32 ext4_encode_extra_time(struct timespec *time)
{
       return cpu_to_le32((sizeof(time->tv_sec) > 4 ?
			   (time->tv_sec >> 32) & EXT4_EPOCH_MASK : 0) |
                          ((time->tv_nsec << EXT4_EPOCH_BITS) & EXT4_NSEC_MASK));
}