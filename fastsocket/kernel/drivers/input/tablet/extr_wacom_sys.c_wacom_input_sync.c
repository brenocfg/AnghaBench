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
struct wacom_combo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_input_dev (struct wacom_combo*) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

void wacom_input_sync(void *wcombo)
{
	input_sync(get_input_dev((struct wacom_combo *)wcombo));
}