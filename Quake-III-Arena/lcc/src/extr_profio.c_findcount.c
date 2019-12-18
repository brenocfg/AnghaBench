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
struct file {char* name; int count; struct count* counts; } ;
struct count {int y; int x; int count; } ;

/* Variables and functions */
 struct file* findfile (char*) ; 

int findcount(char *file, int x, int y) {
	static struct file *cursor;

	if (cursor == 0 || cursor->name != file)
		cursor = findfile(file);
	if (cursor) {
		int l, u;
		struct count *c = cursor->counts;
		for (l = 0, u = cursor->count - 1; l <= u; ) {
			int k = (l + u)/2;
			if (c[k].y > y || c[k].y == y && c[k].x > x)
				u = k - 1;
			else if (c[k].y < y || c[k].y == y && c[k].x < x)
				l = k + 1;
			else
				return c[k].count;
		}
	}
	return -1;
}