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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub_state_post_print (void*) ; 
 int /*<<< orphan*/  stub_state_pre_print (void*) ; 

__attribute__((used)) static int stub_read_bool(int value, void * data)
{
   stub_state_pre_print(data);
   if (value)
      printf("true");
   else
      printf("false");
   stub_state_post_print(data);
   return 0;
}