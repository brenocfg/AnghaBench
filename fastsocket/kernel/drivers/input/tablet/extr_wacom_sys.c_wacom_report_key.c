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
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned int,int) ; 

void wacom_report_key(void *wcombo, unsigned int key_type, int key_data)
{
	input_report_key(get_input_dev((struct wacom_combo *)wcombo), key_type, key_data);
}