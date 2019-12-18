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
struct TYPE_2__ {unsigned int channels; int /*<<< orphan*/  format; } ;
struct pcm {TYPE_1__ config; } ;

/* Variables and functions */
 int pcm_format_to_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pcm_frames_to_bytes(const struct pcm *pcm, unsigned int frames)
{
   return frames * pcm->config.channels *
      (pcm_format_to_bits(pcm->config.format) >> 3);
}