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
struct cmd_list_element {scalar_t__ hook_in; } ;

/* Variables and functions */

__attribute__((used)) static void
clear_hook_in_cleanup (void *data)
{
  struct cmd_list_element *c = data;
  c->hook_in = 0; /* Allow hook to work again once it is complete */
}