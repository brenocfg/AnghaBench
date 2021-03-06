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
typedef  int /*<<< orphan*/  uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_random (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_random_setflags (int /*<<< orphan*/ ) ; 

void
uuid_generate_random(uuid_t out)
{
	read_random(out, sizeof(uuid_t));
	uuid_random_setflags(out);
}