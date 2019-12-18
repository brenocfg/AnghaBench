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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_vfs_pwrite (int,void const*,size_t,int /*<<< orphan*/ ) ; 

ssize_t pwrite(int fd, const void *src, size_t size, off_t offset)
{
    return esp_vfs_pwrite(fd, src, size, offset);
}