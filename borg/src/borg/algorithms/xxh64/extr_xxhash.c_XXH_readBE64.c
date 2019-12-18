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
typedef  int /*<<< orphan*/  U64 ;

/* Variables and functions */
 scalar_t__ XXH_CPU_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  XXH_read64 (void const*) ; 
 int /*<<< orphan*/  XXH_swap64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static U64 XXH_readBE64(const void* ptr)
{
    return XXH_CPU_LITTLE_ENDIAN ? XXH_swap64(XXH_read64(ptr)) : XXH_read64(ptr);
}