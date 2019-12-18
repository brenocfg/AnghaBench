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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct s6000_runtime_data* private_data; } ;
struct s6000_runtime_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct s6000_runtime_data*) ; 

__attribute__((used)) static int s6000_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct s6000_runtime_data *prtd = runtime->private_data;

	kfree(prtd);

	return 0;
}