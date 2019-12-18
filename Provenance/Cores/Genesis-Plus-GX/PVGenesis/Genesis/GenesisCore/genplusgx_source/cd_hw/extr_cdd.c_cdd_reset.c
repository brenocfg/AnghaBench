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
struct TYPE_2__ {int volume; scalar_t__* audio; scalar_t__ loaded; int /*<<< orphan*/  status; scalar_t__ lba; scalar_t__ index; scalar_t__ latency; scalar_t__ cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_STOP ; 
 int /*<<< orphan*/  NO_DISC ; 
 TYPE_1__ cdd ; 

void cdd_reset(void)
{
  /* reset cycle counter */
  cdd.cycles = 0;
  
  /* reset drive access latency */
  cdd.latency = 0;
  
  /* reset track index */
  cdd.index = 0;
  
  /* reset logical block address */
  cdd.lba = 0;

  /* reset status */
  cdd.status = cdd.loaded ? CD_STOP : NO_DISC;
  
  /* reset CD-DA fader (full volume) */
  cdd.volume = 0x400;

  /* clear CD-DA output */
  cdd.audio[0] = cdd.audio[1] = 0;
}