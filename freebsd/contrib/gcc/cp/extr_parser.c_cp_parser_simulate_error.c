#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* context; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PARSER_STATUS_KIND_ERROR ; 
 scalar_t__ cp_parser_uncommitted_to_tentative_parse_p (TYPE_2__*) ; 

__attribute__((used)) static bool
cp_parser_simulate_error (cp_parser* parser)
{
  if (cp_parser_uncommitted_to_tentative_parse_p (parser))
    {
      parser->context->status = CP_PARSER_STATUS_KIND_ERROR;
      return true;
    }
  return false;
}