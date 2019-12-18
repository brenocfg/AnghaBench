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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int unzSeek64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int unzSeek(unzFile file, int32_t offset, int origin)
{
    return unzSeek64(file, offset, origin);
}