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
struct isowbuf_t {int read; } ;

/* Variables and functions */

__attribute__((used)) static inline int isowbuf_poscmp(struct isowbuf_t *iwb, int a, int b)
{
	int read;
	if (a == b)
		return 0;
	read = iwb->read;
	if (a < b) {
		if (a < read && read <= b)
			return +1;
		else
			return -1;
	} else {
		if (b < read && read <= a)
			return -1;
		else
			return +1;
	}
}