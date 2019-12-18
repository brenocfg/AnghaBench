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
struct TYPE_4__ {int buf_pos; int buf_len; int* buf; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ FFTextReader ;

/* Variables and functions */
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ ) ; 
 int ff_text_r8 (TYPE_1__*) ; 

int ff_text_peek_r8(FFTextReader *r)
{
    int c;
    if (r->buf_pos < r->buf_len)
        return r->buf[r->buf_pos];
    c = ff_text_r8(r);
    if (!avio_feof(r->pb)) {
        r->buf_pos = 0;
        r->buf_len = 1;
        r->buf[0] = c;
    }
    return c;
}