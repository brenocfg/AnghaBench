#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t cursor; scalar_t__ name; } ;
typedef  TYPE_1__ param_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static void on_form_data_name(void* context, const char* buf, size_t len)
{
	param_parser_t* parser = (param_parser_t*)context;
	if (len + parser->cursor > 31)
		return;
	memcpy(parser->name + parser->cursor, buf, len);
	parser->cursor += len;
}