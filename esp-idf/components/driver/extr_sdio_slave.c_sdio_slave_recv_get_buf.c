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
typedef  int /*<<< orphan*/ * sdio_slave_buf_handle_t ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ buf_desc_t ;

/* Variables and functions */

uint8_t* sdio_slave_recv_get_buf(sdio_slave_buf_handle_t handle, size_t *len_o)
{
    buf_desc_t *desc = (buf_desc_t*)handle;
    if (handle == NULL) return NULL;

    if (len_o!= NULL) *len_o= desc->length;
    return desc->buf;
}