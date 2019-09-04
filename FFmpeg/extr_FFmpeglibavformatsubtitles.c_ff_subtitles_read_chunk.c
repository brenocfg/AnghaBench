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
struct TYPE_3__ {int /*<<< orphan*/ * pb; scalar_t__ type; scalar_t__ buf_len; scalar_t__ buf_pos; } ;
typedef  TYPE_1__ FFTextReader ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  ff_subtitles_read_text_chunk (TYPE_1__*,int /*<<< orphan*/ *) ; 

void ff_subtitles_read_chunk(AVIOContext *pb, AVBPrint *buf)
{
    FFTextReader tr;
    tr.buf_pos = tr.buf_len = 0;
    tr.type = 0;
    tr.pb = pb;
    ff_subtitles_read_text_chunk(&tr, buf);
}