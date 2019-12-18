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
typedef  int uint8_t ;
struct TYPE_3__ {int size; int* data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

__attribute__((used)) static void make_empty_pgs( hb_buffer_t * buf )
{
    hb_buffer_t * b = buf;
    uint8_t done = 0;

    // Each buffer is composed of 1 or more segments.
    // Segment header is:
    //      type   - 1 byte
    //      length - 2 bytes
    // We want to modify the presentation segment which is type 0x16
    //
    // Note that every pgs display set is required to have a presentation
    // segment, so we will only have to look at one display set.
    while ( b && !done )
    {
        int ii = 0;

        while (ii + 3 <= b->size)
        {
            uint8_t type;
            int len;
            int segment_len_pos;

            type = b->data[ii++];
            segment_len_pos = ii;
            len = ((int)b->data[ii] << 8) + b->data[ii+1];
            ii += 2;

            if (type == 0x16 && ii + len <= b->size)
            {
                int obj_count;
                int kk, jj = ii;
                int obj_start;

                // Skip
                // video descriptor 5 bytes
                // composition descriptor 3 bytes
                // palette update flg 1 byte
                // palette id ref 1 byte
                jj += 10;

                // Set number of composition objects to 0
                obj_count = b->data[jj];
                b->data[jj] = 0;
                jj++;
                obj_start = jj;

                // And remove all the composition objects
                for (kk = 0; kk < obj_count; kk++)
                {
                    uint8_t crop;

                    crop = b->data[jj + 3];
                    // skip
                    // object id - 2 bytes
                    // window id - 1 byte
                    // object/forced flag - 1 byte
                    // x pos - 2 bytes
                    // y pos - 2 bytes
                    jj += 8;
                    if (crop & 0x80)
                    {
                        // skip
                        // crop x - 2 bytes
                        // crop y - 2 bytes
                        // crop w - 2 bytes
                        // crop h - 2 bytes
                        jj += 8;
                    }
                }
                if (jj < b->size)
                {
                    memmove(b->data + obj_start, b->data + jj, b->size - jj);
                }
                b->size = obj_start + ( b->size - jj );
                done = 1;
                len = obj_start - (segment_len_pos + 2);
                b->data[segment_len_pos] = len >> 8;
                b->data[segment_len_pos+1] = len & 0xff;
                break;
            }
            ii += len;
        }
        b = b->next;
    }
}