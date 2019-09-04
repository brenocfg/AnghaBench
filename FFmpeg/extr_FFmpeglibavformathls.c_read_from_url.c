#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct segment {scalar_t__ size; } ;
struct playlist {scalar_t__ cur_seg_offset; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int FFMIN (int,scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_from_url(struct playlist *pls, struct segment *seg,
                         uint8_t *buf, int buf_size)
{
    int ret;

     /* limit read if the segment was only a part of a file */
    if (seg->size >= 0)
        buf_size = FFMIN(buf_size, seg->size - pls->cur_seg_offset);

    ret = avio_read(pls->input, buf, buf_size);
    if (ret > 0)
        pls->cur_seg_offset += ret;

    return ret;
}