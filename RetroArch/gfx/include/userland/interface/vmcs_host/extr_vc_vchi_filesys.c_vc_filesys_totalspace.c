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
 int /*<<< orphan*/  VC_FILESYS_TOTALSPACE ; 
 int vc_filesys_single_string (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

int vc_filesys_totalspace(const char *path)
{
   return vc_filesys_single_string(0, path, VC_FILESYS_TOTALSPACE, 1);
}