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
struct TYPE_3__ {unsigned int* usage; } ;
struct hid_parser {scalar_t__ collection_stack_ptr; int* collection_stack; TYPE_2__* device; TYPE_1__ local; } ;
struct hid_collection {unsigned int type; unsigned int usage; scalar_t__ level; } ;
struct TYPE_4__ {int maxcollection; int collection_size; int /*<<< orphan*/  maxapplication; struct hid_collection* collection; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HID_COLLECTION_APPLICATION ; 
 scalar_t__ HID_COLLECTION_STACK_SIZE ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  kfree (struct hid_collection*) ; 
 struct hid_collection* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct hid_collection*,struct hid_collection*,int) ; 
 int /*<<< orphan*/  memset (struct hid_collection*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int open_collection(struct hid_parser *parser, unsigned type)
{
	struct hid_collection *collection;
	unsigned usage;

	usage = parser->local.usage[0];

	if (parser->collection_stack_ptr == HID_COLLECTION_STACK_SIZE) {
		dbg_hid("collection stack overflow\n");
		return -1;
	}

	if (parser->device->maxcollection == parser->device->collection_size) {
		collection = kmalloc(sizeof(struct hid_collection) *
				parser->device->collection_size * 2, GFP_KERNEL);
		if (collection == NULL) {
			dbg_hid("failed to reallocate collection array\n");
			return -1;
		}
		memcpy(collection, parser->device->collection,
			sizeof(struct hid_collection) *
			parser->device->collection_size);
		memset(collection + parser->device->collection_size, 0,
			sizeof(struct hid_collection) *
			parser->device->collection_size);
		kfree(parser->device->collection);
		parser->device->collection = collection;
		parser->device->collection_size *= 2;
	}

	parser->collection_stack[parser->collection_stack_ptr++] =
		parser->device->maxcollection;

	collection = parser->device->collection +
		parser->device->maxcollection++;
	collection->type = type;
	collection->usage = usage;
	collection->level = parser->collection_stack_ptr - 1;

	if (type == HID_COLLECTION_APPLICATION)
		parser->device->maxapplication++;

	return 0;
}