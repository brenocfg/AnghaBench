#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long file_size; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 long lseek_obj (TYPE_1__*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lseek_end(MY_OBJ * obj, long offset)
{
    long actual = lseek_obj(obj, offset, SEEK_END);

    if (offset == 0L && actual > offset) {
	obj->file_size = actual;
    }
}