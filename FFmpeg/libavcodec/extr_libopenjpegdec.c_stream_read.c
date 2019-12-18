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
struct TYPE_2__ {scalar_t__ pos; scalar_t__ size; int buffer; } ;
typedef  int OPJ_SIZE_T ;
typedef  TYPE_1__ BufferReader ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int,int) ; 

__attribute__((used)) static OPJ_SIZE_T stream_read(void *out_buffer, OPJ_SIZE_T nb_bytes, void *user_data)
{
    BufferReader *reader = user_data;
    int remaining;

    if (reader->pos == reader->size) {
        return (OPJ_SIZE_T)-1;
    }
    remaining = reader->size - reader->pos;
    if (nb_bytes > remaining) {
        nb_bytes = remaining;
    }
    memcpy(out_buffer, reader->buffer + reader->pos, nb_bytes);
    reader->pos += (int)nb_bytes;
    return nb_bytes;
}