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
typedef  unsigned long long uint64_t ;
struct timespec {unsigned long long tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  nanotime (struct timespec*) ; 

__attribute__((used)) static uint64_t
read_time(void)
{
	struct timespec tv;

	nanotime(&tv);

	return (tv.tv_sec * 10000000ULL) + (tv.tv_nsec / 100ULL) + 0x01B21DD213814000ULL;
}