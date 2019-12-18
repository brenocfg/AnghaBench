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

/* Variables and functions */
 int SelectSlider (int,int,int,int,int,char const*,int,int,void (*) (char*,int,void*),void*) ; 

__attribute__((used)) static int BasicUISelectSlider(char const *title, int start_value, int max_value,
                               void (*label_fun)(char *label, int value, void *user_data),
                               void *user_data)
{
	return SelectSlider(0x9a, 0x94, 3, 11, 32, title, start_value, max_value,
			    label_fun, user_data);
}