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
typedef  int /*<<< orphan*/  Wal ;
typedef  int /*<<< orphan*/  Jobrec ;

/* Variables and functions */
 int reserve (int /*<<< orphan*/ *,int) ; 

int
walresvupdate(Wal *w)
{
    int z = 0;
    z +=sizeof(int);
    z +=sizeof(Jobrec);
    return reserve(w, z);
}