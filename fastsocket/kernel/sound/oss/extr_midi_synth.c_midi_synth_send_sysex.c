#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* outputc ) (int,unsigned char) ;} ;
struct TYPE_3__ {int midi_dev; } ;

/* Variables and functions */
 TYPE_2__** midi_devs ; 
 int /*<<< orphan*/  prefix_cmd (int,int) ; 
 int /*<<< orphan*/  stub1 (int,unsigned char) ; 
 int /*<<< orphan*/  stub2 (int,unsigned char) ; 
 TYPE_1__** synth_devs ; 
 int* sysex_state ; 

int
midi_synth_send_sysex(int dev, unsigned char *bytes, int len)
{
	int             orig_dev = synth_devs[dev]->midi_dev;
	int             i;

	for (i = 0; i < len; i++)
	  {
		  switch (bytes[i])
		    {
		    case 0xf0:	/* Start sysex */
			    if (!prefix_cmd(orig_dev, 0xf0))
				    return 0;
			    sysex_state[dev] = 1;
			    break;

		    case 0xf7:	/* End sysex */
			    if (!sysex_state[dev])	/* Orphan sysex end */
				    return 0;
			    sysex_state[dev] = 0;
			    break;

		    default:
			    if (!sysex_state[dev])
				    return 0;

			    if (bytes[i] & 0x80)	/* Error. Another message before sysex end */
			      {
				      bytes[i] = 0xf7;	/* Sysex end */
				      sysex_state[dev] = 0;
			      }
		    }

		  if (!midi_devs[orig_dev]->outputc(orig_dev, bytes[i]))
		    {
/*
 * Hardware level buffer is full. Abort the sysex message.
 */

			    int             timeout = 0;

			    bytes[i] = 0xf7;
			    sysex_state[dev] = 0;

			    while (!midi_devs[orig_dev]->outputc(orig_dev, bytes[i]) &&
				   timeout < 1000)
				    timeout++;
		    }
		  if (!sysex_state[dev])
			  return 0;
	  }

	return 0;
}