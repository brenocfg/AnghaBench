#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* context; int /*<<< orphan*/  cascade; } ;
typedef  TYPE_2__ scd_param_parser_t ;
struct TYPE_3__ {int /*<<< orphan*/  face; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void uri_scd_on_model_string(void* context, char* string)
{
	scd_param_parser_t* parser = (scd_param_parser_t*)context;
	if (strcmp(string, "face") == 0)
		parser->cascade = parser->context->face;
}