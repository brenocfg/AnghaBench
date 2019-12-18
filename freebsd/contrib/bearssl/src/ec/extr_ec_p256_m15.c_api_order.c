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

/* Variables and functions */
 unsigned char const* P256_N ; 

__attribute__((used)) static const unsigned char *
api_order(int curve, size_t *len)
{
	(void)curve;
	*len = sizeof P256_N;
	return P256_N;
}