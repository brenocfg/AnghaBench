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
 int FMODE_READ ; 
 int /*<<< orphan*/  lcd_clear_display () ; 
 scalar_t__ lcd_must_clear ; 
 scalar_t__ lcd_open_cnt ; 

__attribute__((used)) static int lcd_open(struct inode *inode, struct file *file)
{
	if (lcd_open_cnt)
		return -EBUSY;	/* open only once at a time */

	if (file->f_mode & FMODE_READ)	/* device is write-only */
		return -EPERM;

	if (lcd_must_clear) {
		lcd_clear_display();
		lcd_must_clear = 0;
	}
	lcd_open_cnt++;
	return 0;
}