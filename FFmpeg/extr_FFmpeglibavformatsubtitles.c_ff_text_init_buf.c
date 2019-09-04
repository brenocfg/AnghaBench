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
struct TYPE_4__ {int /*<<< orphan*/  buf_pb; } ;
typedef  TYPE_1__ FFTextReader ;

/* Variables and functions */
 int /*<<< orphan*/  ff_text_init_avio (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_text_init_buf(FFTextReader *r, void *buf, size_t size)
{
    memset(&r->buf_pb, 0, sizeof(r->buf_pb));
    ffio_init_context(&r->buf_pb, buf, size, 0, NULL, NULL, NULL, NULL);
    ff_text_init_avio(NULL, r, &r->buf_pb);
}