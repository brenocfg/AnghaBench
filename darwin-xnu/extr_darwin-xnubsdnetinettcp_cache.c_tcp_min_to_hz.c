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
typedef  int uint32_t ;

/* Variables and functions */
 int TCP_RETRANSHZ ; 

__attribute__((used)) static uint32_t tcp_min_to_hz(uint32_t minutes)
{
	if (minutes > 65536)
		return ((uint32_t)65536 * 60 * TCP_RETRANSHZ);

	return (minutes * 60 * TCP_RETRANSHZ);
}