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

__attribute__((used)) static int
hex_to_dec(char c)
{

	switch (c) {
	case '0':
		return (0);
	case '1':
		return (1);
	case '2':
		return (2);
	case '3':
		return (3);
	case '4':
		return (4);
	case '5':
		return (5);
	case '6':
		return (6);
	case '7':
		return (7);
	case '8':
		return (8);
	case '9':
		return (9);
	case 'a':
		return (10);
	case 'b':
		return (11);
	case 'c':
		return (12);
	case 'd':
		return (13);
	case 'e':
		return (14);
	case 'f':
		return (15);
	default:
		return (-1);
	}
}