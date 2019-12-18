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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* repl_text_base ; 
 char* repl_text_limit ; 
 char* repl_write_ptr ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
output_bytes (const char *str, size_t len)
{
  if ((repl_write_ptr + 1) + len >= repl_text_limit)
    {
      size_t new_size = (repl_text_limit - repl_text_base) << 1;
      char *new_buf = xrealloc (repl_text_base, new_size);

      repl_write_ptr = new_buf + (repl_write_ptr - repl_text_base);
      repl_text_base = new_buf;
      repl_text_limit = new_buf + new_size;
    }
  memcpy (repl_write_ptr + 1, str, len);
  repl_write_ptr += len;
}