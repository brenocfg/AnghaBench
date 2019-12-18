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
struct TYPE_3__ {int /*<<< orphan*/  al_elements; } ;
typedef  TYPE_1__ alist_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_stats (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
alist_stats(alist_t *alist, int verbose)
{
	printf("Alist statistics\n");
	hash_stats(alist->al_elements, verbose);
}