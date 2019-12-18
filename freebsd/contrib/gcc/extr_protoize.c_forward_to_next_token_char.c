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
 scalar_t__ ISSPACE (unsigned char const) ; 
 int /*<<< orphan*/  check_source (int,int /*<<< orphan*/ ) ; 
 char const* clean_text_limit ; 

__attribute__((used)) static const char *
forward_to_next_token_char (const char *ptr)
{
  for (++ptr; ISSPACE ((const unsigned char)*ptr);
       check_source (++ptr < clean_text_limit, 0))
    continue;
  return ptr;
}