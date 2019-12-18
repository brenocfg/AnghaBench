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
struct inode {int dummy; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 scalar_t__ keypad_buflen ; 
 scalar_t__ keypad_open_cnt ; 

__attribute__((used)) static int keypad_open(struct inode *inode, struct file *file)
{

	if (keypad_open_cnt)
		return -EBUSY;	/* open only once at a time */

	if (file->f_mode & FMODE_WRITE)	/* device is read-only */
		return -EPERM;

	keypad_buflen = 0;	/* flush the buffer on opening */
	keypad_open_cnt++;
	return 0;
}