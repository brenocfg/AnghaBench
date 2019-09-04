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
typedef  int /*<<< orphan*/  ebb_buf ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ dpm_param_parser_t ;

/* Variables and functions */

__attribute__((used)) static void uri_dpm_on_source_blob(void* context, ebb_buf data)
{
	dpm_param_parser_t* parser = (dpm_param_parser_t*)context;
	parser->source = data;
}