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
struct TYPE_3__ {int /*<<< orphan*/ * buffer; scalar_t__ count; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  Byte ;
typedef  TYPE_1__ Buffer ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

Byte *
Buf_Destroy(Buffer *buf, Boolean freeData)
{
    Byte *data;

    data = buf->buffer;
    if (freeData) {
	free(data);
	data = NULL;
    }

    buf->size = 0;
    buf->count = 0;
    buf->buffer = NULL;

    return data;
}