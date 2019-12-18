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
struct TYPE_4__ {scalar_t__ size; int count; int /*<<< orphan*/  buffer; } ;
typedef  scalar_t__ Byte ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 scalar_t__ BUF_COMPACT_LIMIT ; 
 scalar_t__* Buf_Destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__* bmake_realloc (int /*<<< orphan*/ ,int) ; 

Byte *
Buf_DestroyCompact(Buffer *buf)
{
#if BUF_COMPACT_LIMIT > 0
    Byte *data;

    if (buf->size - buf->count >= BUF_COMPACT_LIMIT) {
	/* We trust realloc to be smart */
	data = bmake_realloc(buf->buffer, buf->count + 1);
	if (data) {
	    data[buf->count] = 0;
	    Buf_Destroy(buf, FALSE);
	    return data;
	}
    }
#endif
    return Buf_Destroy(buf, FALSE);
}