#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_timer_user {TYPE_1__* timeri; } ;
struct file {struct snd_timer_user* private_data; } ;
struct TYPE_2__ {scalar_t__ lost; } ;

/* Variables and functions */
 int EBADFD ; 
 int snd_timer_continue (TYPE_1__*) ; 

__attribute__((used)) static int snd_timer_user_continue(struct file *file)
{
	int err;
	struct snd_timer_user *tu;

	tu = file->private_data;
	if (!tu->timeri)
		return -EBADFD;
	tu->timeri->lost = 0;
	return (err = snd_timer_continue(tu->timeri)) < 0 ? err : 0;
}