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
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  parse_events__delete_buffer (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  parse_events__flush_buffer (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  parse_events__scan_string (char const*,void*) ; 
 int parse_events_debug ; 
 int /*<<< orphan*/  parse_events_lex_destroy (void*) ; 
 int parse_events_lex_init_extra (int,void**) ; 
 int parse_events_parse (void*,void*) ; 

__attribute__((used)) static int parse_events__scanner(const char *str, void *data, int start_token)
{
	YY_BUFFER_STATE buffer;
	void *scanner;
	int ret;

	ret = parse_events_lex_init_extra(start_token, &scanner);
	if (ret)
		return ret;

	buffer = parse_events__scan_string(str, scanner);

#ifdef PARSER_DEBUG
	parse_events_debug = 1;
#endif
	ret = parse_events_parse(data, scanner);

	parse_events__flush_buffer(buffer, scanner);
	parse_events__delete_buffer(buffer, scanner);
	parse_events_lex_destroy(scanner);
	return ret;
}