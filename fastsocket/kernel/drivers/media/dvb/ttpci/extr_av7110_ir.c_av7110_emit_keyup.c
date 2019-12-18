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
struct infrared {TYPE_1__* input_dev; int /*<<< orphan*/  last_key; } ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void av7110_emit_keyup(unsigned long parm)
{
	struct infrared *ir = (struct infrared *) parm;

	if (!ir || !test_bit(ir->last_key, ir->input_dev->key))
		return;

	input_report_key(ir->input_dev, ir->last_key, 0);
	input_sync(ir->input_dev);
}