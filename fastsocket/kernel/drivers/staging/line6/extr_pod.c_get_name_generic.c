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
struct usb_line6_pod {int /*<<< orphan*/  dumpreq; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int POD_NAME_LENGTH ; 
 int line6_wait_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t get_name_generic(struct usb_line6_pod *pod, const char *str, char *buf)
{
	int length = 0;
	const char *p1;
	char *p2;
	char *last_non_space = buf;

	int retval = line6_wait_dump(&pod->dumpreq, 0);
	if (retval < 0)
		return retval;

	for (p1 = str, p2 = buf; *p1; ++p1, ++p2) {
		*p2 = *p1;
		if (*p2 != ' ')
			last_non_space = p2;
		if (++length == POD_NAME_LENGTH)
			break;
	}

	*(last_non_space + 1) = '\n';
	return last_non_space - buf + 2;
}