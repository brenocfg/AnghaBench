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
struct snd_tea575x {int /*<<< orphan*/  in_use; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_tea575x* video_drvdata (struct file*) ; 

__attribute__((used)) static int snd_tea575x_exclusive_open(struct file *file)
{
	struct snd_tea575x *tea = video_drvdata(file);

	return test_and_set_bit(0, &tea->in_use) ? -EBUSY : 0;
}