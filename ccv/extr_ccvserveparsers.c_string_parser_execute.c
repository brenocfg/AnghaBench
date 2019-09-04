#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t cursor; scalar_t__ state; scalar_t__ string; } ;
typedef  TYPE_1__ string_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CLI_INFO ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 scalar_t__ s_string_overflow ; 
 scalar_t__ s_string_start ; 

void string_parser_execute(string_parser_t* parser, const char* buf, size_t len)
{
	if (parser->cursor + len > sizeof(parser->string) - 1)
	{
		PRINT(CCV_CLI_INFO, "string parameter overflow %zu\n", sizeof(parser->string));
		parser->state = s_string_overflow;
	}
	else if (parser->state == s_string_start) {
		memcpy(parser->string + parser->cursor, buf, len);
		parser->cursor += len;
	}
}