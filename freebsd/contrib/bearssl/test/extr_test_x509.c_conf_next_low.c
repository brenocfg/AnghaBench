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
 int EOF ; 
 int /*<<< orphan*/  conf ; 
 int conf_delayed_char ; 
 int /*<<< orphan*/  conf_linenum ; 
 int fgetc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
conf_next_low(void)
{
	int x;

	x = conf_delayed_char;
	if (x >= 0) {
		conf_delayed_char = -1;
	} else {
		x = fgetc(conf);
		if (x == EOF) {
			x = -1;
		}
	}
	if (x == '\r') {
		x = fgetc(conf);
		if (x == EOF) {
			x = -1;
		}
		if (x != '\n') {
			conf_delayed_char = x;
			x = '\n';
		}
	}
	if (x == '\n') {
		conf_linenum ++;
	}
	return x;
}