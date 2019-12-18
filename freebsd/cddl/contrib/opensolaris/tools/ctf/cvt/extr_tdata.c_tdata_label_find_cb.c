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
struct TYPE_2__ {int /*<<< orphan*/  le_name; } ;
typedef  TYPE_1__ labelent_t ;

/* Variables and functions */
 int streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tdata_label_find_cb(void *arg1, void *arg2)
{
	labelent_t *le = arg1;
	labelent_t *tmpl = arg2;
	return (streq(le->le_name, tmpl->le_name));
}