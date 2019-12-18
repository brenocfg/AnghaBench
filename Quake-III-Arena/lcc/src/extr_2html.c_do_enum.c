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
typedef  TYPE_1__* rcc_enum__ty ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void do_enum(void *x) {
	rcc_enum__ty e = x;

	do_identifier(e->id);
	printf("=");
	do_int(e->value);
}