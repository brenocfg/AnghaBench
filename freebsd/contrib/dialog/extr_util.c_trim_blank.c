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
 int /*<<< orphan*/  UCH (char) ; 
 int isblank (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
trim_blank(char *base, char *dst)
{
    int count = isblank(UCH(*dst));

    while (dst-- != base) {
	if (*dst == '\n') {
	    break;
	} else if (isblank(UCH(*dst))) {
	    count++;
	} else {
	    break;
	}
    }
    return (count > 1);
}