#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ parameters; scalar_t__ raw_bits; } ;
typedef  TYPE_1__ FLAC__EntropyCodingMethod_PartitionedRiceContents ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int /*<<< orphan*/  FLAC__format_entropy_coding_method_partitioned_rice_contents_init (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void FLAC__format_entropy_coding_method_partitioned_rice_contents_clear(FLAC__EntropyCodingMethod_PartitionedRiceContents *object)
{
	FLAC__ASSERT(0 != object);

	if(0 != object->parameters)
		free(object->parameters);
	if(0 != object->raw_bits)
		free(object->raw_bits);
	FLAC__format_entropy_coding_method_partitioned_rice_contents_init(object);
}