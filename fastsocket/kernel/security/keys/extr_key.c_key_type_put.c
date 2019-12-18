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
struct key_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_types_sem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void key_type_put(struct key_type *ktype)
{
	up_read(&key_types_sem);
}