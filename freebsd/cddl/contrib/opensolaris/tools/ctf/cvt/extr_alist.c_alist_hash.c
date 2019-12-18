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
struct TYPE_2__ {int /*<<< orphan*/  ale_name; } ;
typedef  TYPE_1__ alist_el_t ;

/* Variables and functions */

__attribute__((used)) static int
alist_hash(int nbuckets, void *arg)
{
	alist_el_t *el = arg;
	uintptr_t num = (uintptr_t)el->ale_name;

	return (num % nbuckets);
}