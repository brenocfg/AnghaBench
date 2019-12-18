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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* rclex_tok ; 
 int rclex_tok_max ; 
 int rclex_tok_pos ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
rclex_tok_add_char (int ch)
{
  if (! rclex_tok || rclex_tok_max <= rclex_tok_pos)
    {
      char *h = xmalloc (rclex_tok_max + 9);

      if (! h)
	abort ();
      if (rclex_tok)
	{
	  memcpy (h, rclex_tok, rclex_tok_pos + 1);
	  free (rclex_tok);
	}
      else
	rclex_tok_pos = 0;
      rclex_tok_max += 8;
      rclex_tok = h;
    }
  if (ch != -1)
    rclex_tok[rclex_tok_pos++] = (char) ch;
  rclex_tok[rclex_tok_pos] = 0;
}