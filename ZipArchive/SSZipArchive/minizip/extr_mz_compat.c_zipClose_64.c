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
typedef  int /*<<< orphan*/  zipFile ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_VERSION_MADEBY ; 
 int zipClose2_64 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int zipClose_64(zipFile file, const char *global_comment)
{
    return zipClose2_64(file, global_comment, MZ_VERSION_MADEBY);
}