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
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int current_device ; 

__attribute__((used)) static int
z2_release(struct gendisk *disk, fmode_t mode)
{
    if ( current_device == -1 )
	return 0;     

    /*
     * FIXME: unmap memory
     */

    return 0;
}