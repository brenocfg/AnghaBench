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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EOF ; 
 int /*<<< orphan*/  c_parser_external_declaration (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 void* obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  parser_obstack ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 

__attribute__((used)) static void
c_parser_translation_unit (c_parser *parser)
{
  if (c_parser_next_token_is (parser, CPP_EOF))
    {
      if (pedantic)
	pedwarn ("ISO C forbids an empty source file");
    }
  else
    {
      void *obstack_position = obstack_alloc (&parser_obstack, 0);
      do
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      while (c_parser_next_token_is_not (parser, CPP_EOF));
    }
}