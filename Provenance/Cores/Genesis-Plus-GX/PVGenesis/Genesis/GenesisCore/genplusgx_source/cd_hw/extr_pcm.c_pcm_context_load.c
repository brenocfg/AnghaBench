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
typedef  int uint8 ;
struct TYPE_2__ {int* chan; int* out; int* bank; int* ram; int enabled; int status; int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  load_param (int*,int) ; 
 TYPE_1__ pcm ; 

int pcm_context_load(uint8 *state)
{
  uint8 tmp8;
  int bufferptr = 0;

  load_param(pcm.chan, sizeof(pcm.chan));
  load_param(pcm.out, sizeof(pcm.out));

  load_param(&tmp8, 1);
  pcm.bank = &pcm.ram[(tmp8 & 0x0f) << 12];

  load_param(&pcm.enabled, sizeof(pcm.enabled));
  load_param(&pcm.status, sizeof(pcm.status));
  load_param(&pcm.index, sizeof(pcm.index));
  load_param(pcm.ram, sizeof(pcm.ram));

  return bufferptr;
}