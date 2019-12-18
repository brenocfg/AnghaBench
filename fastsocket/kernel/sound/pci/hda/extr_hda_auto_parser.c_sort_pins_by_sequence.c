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
struct auto_out_pin {int /*<<< orphan*/  pin; } ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  compare_seq ; 
 int /*<<< orphan*/  sort (struct auto_out_pin*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_pins_by_sequence(hda_nid_t *pins, struct auto_out_pin *list,
				  int num_pins)
{
	int i;
	sort(list, num_pins, sizeof(list[0]), compare_seq, NULL);
	for (i = 0; i < num_pins; i++)
		pins[i] = list[i].pin;
}