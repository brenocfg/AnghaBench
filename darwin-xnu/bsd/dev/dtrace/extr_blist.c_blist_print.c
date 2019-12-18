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
typedef  TYPE_1__* blist_t ;
struct TYPE_3__ {int /*<<< orphan*/  bl_skip; int /*<<< orphan*/  bl_radix; int /*<<< orphan*/  bl_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  blst_radix_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
blist_print(blist_t bl)
{
	printf("BLIST {\n");
	blst_radix_print(bl->bl_root, 0, bl->bl_radix, bl->bl_skip, 4);
	printf("}\n");
}