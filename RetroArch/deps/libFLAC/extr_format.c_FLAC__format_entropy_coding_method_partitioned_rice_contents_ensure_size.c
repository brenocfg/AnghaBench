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
struct TYPE_3__ {unsigned int capacity_by_order; unsigned int* parameters; unsigned int* raw_bits; } ;
typedef  int FLAC__bool ;
typedef  TYPE_1__ FLAC__EntropyCodingMethod_PartitionedRiceContents ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ safe_realloc_ (unsigned int*,int) ; 

FLAC__bool FLAC__format_entropy_coding_method_partitioned_rice_contents_ensure_size(FLAC__EntropyCodingMethod_PartitionedRiceContents *object, unsigned max_partition_order)
{
	FLAC__ASSERT(0 != object);

	FLAC__ASSERT(object->capacity_by_order > 0 || (0 == object->parameters && 0 == object->raw_bits));

	if(object->capacity_by_order < max_partition_order) {
		if(0 == (object->parameters = (unsigned int*)safe_realloc_(object->parameters, sizeof(unsigned)*(1 << max_partition_order))))
			return false;
		if(0 == (object->raw_bits = (unsigned int*)safe_realloc_(object->raw_bits, sizeof(unsigned)*(1 << max_partition_order))))
			return false;
		memset(object->raw_bits, 0, sizeof(unsigned)*(1 << max_partition_order));
		object->capacity_by_order = max_partition_order;
	}

	return true;
}