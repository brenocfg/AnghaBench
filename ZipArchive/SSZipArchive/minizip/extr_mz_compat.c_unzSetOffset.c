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
typedef  int /*<<< orphan*/  unzFile ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int unzSetOffset64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unzSetOffset(unzFile file, uint32_t pos)
{
    return unzSetOffset64(file, pos);
}