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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,unsigned long long) ; 
 int /*<<< orphan*/  stub_state_post_print (void*) ; 
 int /*<<< orphan*/  stub_state_pre_print (void*) ; 

__attribute__((used)) static int stub_read_uint(uint64_t value, void *data)
{
   stub_state_pre_print(data);
#ifdef _WIN32
   printf("%I64u", (unsigned long long)value);
#else
   printf("%llu", (unsigned long long)value);
#endif
   stub_state_post_print(data);
   return 0;
}