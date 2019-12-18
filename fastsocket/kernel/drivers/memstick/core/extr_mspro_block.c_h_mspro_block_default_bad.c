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
struct memstick_request {int dummy; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int h_mspro_block_default_bad(struct memstick_dev *card,
				     struct memstick_request **mrq)
{
	return -ENXIO;
}