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
 int /*<<< orphan*/  cpp_pipe ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int rclex_lastch ; 
 int /*<<< orphan*/  rclex_tok_add_char (int) ; 

__attribute__((used)) static int
rclex_readch (void)
{
  int r = -1;

  if ((r = rclex_lastch) != -1)
    rclex_lastch = -1;
  else
    {
      char ch;
      do
        {
	  if (! cpp_pipe || feof (cpp_pipe)
	      || fread (&ch, 1, 1,cpp_pipe) != 1)
	    break;
	  r = ((int) ch) & 0xff;
        }
      while (r == 0 || r == '\r');
  }
  rclex_tok_add_char (r);
  return r;
}