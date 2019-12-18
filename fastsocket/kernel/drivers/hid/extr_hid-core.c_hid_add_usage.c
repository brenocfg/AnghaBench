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
struct TYPE_2__ {size_t usage_index; unsigned int* usage; int /*<<< orphan*/ * collection_index; } ;
struct hid_parser {int collection_stack_ptr; TYPE_1__ local; int /*<<< orphan*/ * collection_stack; } ;

/* Variables and functions */
 size_t HID_MAX_USAGES ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 

__attribute__((used)) static int hid_add_usage(struct hid_parser *parser, unsigned usage)
{
	if (parser->local.usage_index >= HID_MAX_USAGES) {
		dbg_hid("usage index exceeded\n");
		return -1;
	}
	parser->local.usage[parser->local.usage_index] = usage;
	parser->local.collection_index[parser->local.usage_index] =
		parser->collection_stack_ptr ?
		parser->collection_stack[parser->collection_stack_ptr - 1] : 0;
	parser->local.usage_index++;
	return 0;
}