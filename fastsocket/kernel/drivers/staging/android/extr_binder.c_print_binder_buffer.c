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
struct binder_buffer {int debug_id; scalar_t__ transaction; int /*<<< orphan*/  offsets_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *print_binder_buffer(char *buf, char *end, const char *prefix,
				 struct binder_buffer *buffer)
{
	buf += snprintf(buf, end - buf, "%s %d: %p size %zd:%zd %s\n",
			prefix, buffer->debug_id, buffer->data,
			buffer->data_size, buffer->offsets_size,
			buffer->transaction ? "active" : "delivered");
	return buf;
}