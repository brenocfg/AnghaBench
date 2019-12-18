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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  sub_tag; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ kd_chunk_header_v3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,TYPE_1__*,int) ; 

int
kdbg_write_v3_chunk_header_to_buffer(void * buffer, uint32_t tag, uint32_t sub_tag, uint64_t length)
{
	kd_chunk_header_v3 header = {
		.tag = tag,
		.sub_tag = sub_tag,
		.length = length,
	};

	if (!buffer) {
		return 0;
	}

	memcpy(buffer, &header, sizeof(kd_chunk_header_v3));

	return (sizeof(kd_chunk_header_v3));
}