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
struct TYPE_3__ {unsigned long cbBuffer; unsigned long BufferType; void* pvBuffer; } ;
typedef  TYPE_1__ SecBuffer ;

/* Variables and functions */

__attribute__((used)) static void init_sec_buffer(SecBuffer *buffer, unsigned long type,
                            void *data, unsigned long size)
{
    buffer->cbBuffer   = size;
    buffer->BufferType = type;
    buffer->pvBuffer   = data;
}