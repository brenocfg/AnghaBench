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
struct TYPE_3__ {scalar_t__ on_release; scalar_t__ written; scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ ebb_buf ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

void uri_ebb_buf_free(ebb_buf* buf)
{
	free(buf->data);
	buf->data = 0;
	buf->len = buf->written = 0;
	buf->on_release = 0;
}