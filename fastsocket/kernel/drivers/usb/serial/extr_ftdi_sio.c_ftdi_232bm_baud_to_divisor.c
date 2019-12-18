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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ftdi_232bm_baud_base_to_divisor (int,int) ; 

__attribute__((used)) static __u32 ftdi_232bm_baud_to_divisor(int baud)
{
	 return ftdi_232bm_baud_base_to_divisor(baud, 48000000);
}