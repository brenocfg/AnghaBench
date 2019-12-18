#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tokens_avail; TYPE_1__* tokens; scalar_t__ error; int /*<<< orphan*/  in_pragma; } ;
typedef  TYPE_2__ c_parser ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_PRAGMA ; 
 scalar_t__ CPP_PRAGMA_EOL ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (!parser->in_pragma || parser->tokens[0].type != CPP_PRAGMA_EOL);
  gcc_assert (parser->error || parser->tokens[0].type != CPP_PRAGMA);
  if (parser->tokens_avail == 2)
    parser->tokens[0] = parser->tokens[1];
  parser->tokens_avail--;
}