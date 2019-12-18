#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_work_private_t ;
struct TYPE_11__ {scalar_t__ split; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int size; scalar_t__ data; TYPE_1__ s; } ;
typedef  TYPE_2__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_splice_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_2__**) ; 
 TYPE_2__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int hb_buffer_list_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_buffer_list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_buffer_list_rem_head (int /*<<< orphan*/ *) ; 
 int hb_buffer_list_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static hb_buffer_t * splice_discontinuity( hb_work_private_t *r, hb_buffer_t *buf )
{
    // Handle buffers that were split across a PCR discontinuity.
    // Rejoin them into a single buffer.
    hb_buffer_list_t * list = get_splice_list(r, buf->s.id);
    if (list != NULL)
    {
        hb_buffer_list_append(list, buf);
        if (buf->s.split)
        {
            return NULL;
        }

        int count = hb_buffer_list_count(list);
        if (count > 1)
        {
            int size = hb_buffer_list_size(list);
            hb_buffer_t * b = hb_buffer_init(size);
            buf = hb_buffer_list_head(list);
            b->s = buf->s;

            int pos = 0;
            while ((buf = hb_buffer_list_rem_head(list)) != NULL)
            {
                memcpy(b->data + pos, buf->data, buf->size);
                pos += buf->size;
                hb_buffer_close(&buf);
            }
            buf = b;
        }
        else
        {
            buf = hb_buffer_list_clear(list);
        }
    }
    return buf;
}