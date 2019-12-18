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

/* Variables and functions */
 int unzOpenCurrentFile3 (int /*<<< orphan*/ ,int*,int*,int,int /*<<< orphan*/ *) ; 

int unzOpenCurrentFile2(unzFile file, int *method, int *level, int raw)
{
    return unzOpenCurrentFile3(file, method, level, raw, NULL);
}