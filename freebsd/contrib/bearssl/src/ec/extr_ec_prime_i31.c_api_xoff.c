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
 int /*<<< orphan*/  api_generator (int,size_t*) ; 

__attribute__((used)) static size_t
api_xoff(int curve, size_t *len)
{
	api_generator(curve, len);
	*len >>= 1;
	return 1;
}