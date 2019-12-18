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
typedef  int __u8 ;

/* Variables and functions */

__attribute__((used)) static inline __u8
bitmap_to_number(__u8 bitmap)
{
	__u8 i;

	for(i=0; i<8 && !(bitmap &(1<<i)); i++)
		;
	return i;
}