#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ x; struct TYPE_13__* link; } ;
struct TYPE_9__ {char* p; } ;
struct TYPE_10__ {TYPE_1__ v; } ;
struct TYPE_11__ {TYPE_2__ c; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
typedef  TYPE_4__* Symbol ;
typedef  TYPE_5__* List ;

/* Variables and functions */
 TYPE_5__* append (int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_5__* filelist ; 
 int /*<<< orphan*/  mkstr (char*) ; 

__attribute__((used)) static int bbfile(char *file) {
	if (file) {
		List lp;
		int i = 1;
		if ((lp = filelist) != NULL)
			do {
				lp = lp->link;
				if (((Symbol)lp->x)->u.c.v.p == file)
					return i;
				i++;
			} while (lp != filelist);
		filelist = append(mkstr(file), filelist);
		return i;
	}
	return 0;
}