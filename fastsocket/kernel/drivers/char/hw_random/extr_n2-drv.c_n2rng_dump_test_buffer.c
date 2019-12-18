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
struct n2rng {int /*<<< orphan*/ * test_buffer; TYPE_1__* op; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SELFTEST_BUFFER_WORDS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n2rng_dump_test_buffer(struct n2rng *np)
{
	int i;

	for (i = 0; i < SELFTEST_BUFFER_WORDS; i++)
		dev_err(&np->op->dev, "Test buffer slot %d [0x%016llx]\n",
			i, np->test_buffer[i]);
}