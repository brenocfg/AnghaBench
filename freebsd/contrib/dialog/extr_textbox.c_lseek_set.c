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
typedef  int /*<<< orphan*/  MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  dlg_exiterr (char*,long,long) ; 
 long lseek_obj (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lseek_set(MY_OBJ * obj, long offset)
{
    long actual = lseek_obj(obj, offset, SEEK_SET);

    if (actual != offset) {
	dlg_exiterr("Cannot set file position to %ld (actual %ld)\n",
		    offset, actual);
    }
}