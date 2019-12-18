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
struct mousedev {size_t minor; } ;

/* Variables and functions */
 struct mousedev** mousedev_table ; 

__attribute__((used)) static int mousedev_install_chrdev(struct mousedev *mousedev)
{
	mousedev_table[mousedev->minor] = mousedev;
	return 0;
}