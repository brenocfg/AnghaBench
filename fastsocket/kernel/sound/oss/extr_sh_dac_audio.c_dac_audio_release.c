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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dac_audio_stop () ; 
 int /*<<< orphan*/  dac_audio_sync () ; 
 scalar_t__ in_use ; 

__attribute__((used)) static int dac_audio_release(struct inode *inode, struct file *file)
{
	dac_audio_sync();
	dac_audio_stop();
	in_use = 0;

	return 0;
}