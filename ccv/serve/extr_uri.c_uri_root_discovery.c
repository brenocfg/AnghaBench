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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ebb_buf ;

/* Variables and functions */

int uri_root_discovery(const void* context, const void* parsed, ebb_buf* buf)
{
	ebb_buf* root_discovery = (ebb_buf*)context;
	buf->data = root_discovery->data;
	buf->len = root_discovery->len;
	return 0;
}