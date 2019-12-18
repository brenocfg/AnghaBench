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
typedef  int /*<<< orphan*/  labelent_t ;

/* Variables and functions */

__attribute__((used)) static int
tdata_label_top_cb(void *data, void *arg)
{
	labelent_t *le = data;
	labelent_t **topp = arg;

	*topp = le;

	return (1);
}