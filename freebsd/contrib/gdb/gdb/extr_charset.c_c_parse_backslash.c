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
 int /*<<< orphan*/  c_parse_backslash_baton ; 
 int c_parse_backslash_func (int /*<<< orphan*/ ,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int,int*) ; 

int
c_parse_backslash (int host_char, int *target_char)
{
  return (*c_parse_backslash_func) (c_parse_backslash_baton,
                                    host_char, target_char);
}