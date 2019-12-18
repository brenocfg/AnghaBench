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
struct saa5249_device {int /*<<< orphan*/  in_use; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_senddata (struct saa5249_device*,int,int,int,...) ; 
 struct saa5249_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa5249_release(struct file *file)
{
	struct saa5249_device *t = video_drvdata(file);

	i2c_senddata(t, 1, 0x20, -1);		/* Turn off CCT */
	i2c_senddata(t, 5, 3, 3, -1);		/* Turn off TV-display */
	clear_bit(0, &t->in_use);
	return 0;
}