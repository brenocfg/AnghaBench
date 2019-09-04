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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ cur_pos; scalar_t__ tail_pos; scalar_t__ out2; scalar_t__ out; } ;
typedef  TYPE_1__ OutputStream ;

/* Variables and functions */
 int /*<<< orphan*/  ffurl_write (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ism_write(void *opaque, uint8_t *buf, int buf_size)
{
    OutputStream *os = opaque;
    if (os->out)
        ffurl_write(os->out, buf, buf_size);
    if (os->out2)
        ffurl_write(os->out2, buf, buf_size);
    os->cur_pos += buf_size;
    if (os->cur_pos >= os->tail_pos)
        os->tail_pos = os->cur_pos;
    return buf_size;
}