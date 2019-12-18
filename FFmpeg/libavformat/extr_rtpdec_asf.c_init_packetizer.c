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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int pos; int /*<<< orphan*/ * buf_end; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  ffio_init_context (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packetizer_read ; 

__attribute__((used)) static void init_packetizer(AVIOContext *pb, uint8_t *buf, int len)
{
    ffio_init_context(pb, buf, len, 0, NULL, packetizer_read, NULL, NULL);

    /* this "fills" the buffer with its current content */
    pb->pos     = len;
    pb->buf_end = buf + len;
}