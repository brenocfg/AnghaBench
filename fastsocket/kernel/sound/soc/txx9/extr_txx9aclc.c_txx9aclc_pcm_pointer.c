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
struct txx9aclc_dmadata {int /*<<< orphan*/  pos; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {struct txx9aclc_dmadata* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t
txx9aclc_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct txx9aclc_dmadata *dmadata = substream->runtime->private_data;

	return bytes_to_frames(substream->runtime, dmadata->pos);
}