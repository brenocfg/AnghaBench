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
struct TYPE_4__ {scalar_t__ data; scalar_t__ written; scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  TYPE_2__ blob_parser_t ;

/* Variables and functions */

void blob_parser_init(blob_parser_t* parser)
{
	parser->data.len = 0;
	parser->data.written = 0;
	parser->data.data = 0;
}