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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VC_FILESYS_CLOSEDIR ; 
 int vc_filesys_single_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vc_filesys_closedir(void *dhandle)
{
   return vc_filesys_single_param((uint32_t)dhandle, VC_FILESYS_CLOSEDIR);
}