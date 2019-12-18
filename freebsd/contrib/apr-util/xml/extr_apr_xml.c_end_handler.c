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
struct TYPE_4__ {TYPE_1__* cur_elem; scalar_t__ error; } ;
typedef  TYPE_2__ apr_xml_parser ;
struct TYPE_3__ {struct TYPE_3__* parent; } ;

/* Variables and functions */

__attribute__((used)) static void end_handler(void *userdata, const char *name)
{
    apr_xml_parser *parser = userdata;

    /* punt once we find an error */
    if (parser->error)
	return;

    /* pop up one level */
    parser->cur_elem = parser->cur_elem->parent;
}