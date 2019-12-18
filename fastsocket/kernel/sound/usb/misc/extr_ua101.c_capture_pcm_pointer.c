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
struct ua101 {int /*<<< orphan*/  capture; } ;
struct snd_pcm_substream {struct ua101* private_data; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  ua101_pcm_pointer (struct ua101*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t capture_pcm_pointer(struct snd_pcm_substream *subs)
{
	struct ua101 *ua = subs->private_data;

	return ua101_pcm_pointer(ua, &ua->capture);
}