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
struct flex_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flex_array_free_parts (struct flex_array*) ; 
 int /*<<< orphan*/  kfree (struct flex_array*) ; 

void flex_array_free(struct flex_array *fa)
{
	flex_array_free_parts(fa);
	kfree(fa);
}