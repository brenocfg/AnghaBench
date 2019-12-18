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
 int /*<<< orphan*/  c_target_char_has_backslash_escape_baton ; 
 char const* c_target_char_has_backslash_escape_func (int /*<<< orphan*/ ,int) ; 
 char const* stub1 (int /*<<< orphan*/ ,int) ; 

const char *
c_target_char_has_backslash_escape (int target_char)
{
  return ((*c_target_char_has_backslash_escape_func)
          (c_target_char_has_backslash_escape_baton, target_char));
}