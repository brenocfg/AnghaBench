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
typedef  int u16 ;
struct rt2x00_rate {int dummy; } ;

/* Variables and functions */
 struct rt2x00_rate const* rt2x00_supported_rates ; 

__attribute__((used)) static inline const struct rt2x00_rate *rt2x00_get_rate(const u16 hw_value)
{
	return &rt2x00_supported_rates[hw_value & 0xff];
}