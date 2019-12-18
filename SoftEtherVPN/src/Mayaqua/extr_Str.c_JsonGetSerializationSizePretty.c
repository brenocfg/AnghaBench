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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;

/* Variables and functions */
 int json_serialize_to_buffer_r (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

UINT JsonGetSerializationSizePretty(JSON_VALUE *value) {
	char num_buf[1100]; /* recursively allocating buffer on stack is a bad idea, so let's do it only once */
	int res = json_serialize_to_buffer_r(value, NULL, 0, 1, num_buf);
	return res < 0 ? 0 : (UINT)(res + 1);
}