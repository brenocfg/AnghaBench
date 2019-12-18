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
typedef  int /*<<< orphan*/  cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 unsigned char* _cpp_unaligned_alloc (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned char* cpp_spell_token (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int cpp_token_len (int /*<<< orphan*/  const*) ; 

unsigned char *
cpp_token_as_text (cpp_reader *pfile, const cpp_token *token)
{ 
  unsigned int len = cpp_token_len (token) + 1;
  unsigned char *start = _cpp_unaligned_alloc (pfile, len), *end;

  end = cpp_spell_token (pfile, token, start, false);
  end[0] = '\0';

  return start;
}