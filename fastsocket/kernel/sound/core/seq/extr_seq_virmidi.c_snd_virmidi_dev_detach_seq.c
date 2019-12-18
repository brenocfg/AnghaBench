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
struct snd_virmidi_dev {int client; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_delete_kernel_client (int) ; 

__attribute__((used)) static void snd_virmidi_dev_detach_seq(struct snd_virmidi_dev *rdev)
{
	if (rdev->client >= 0) {
		snd_seq_delete_kernel_client(rdev->client);
		rdev->client = -1;
	}
}