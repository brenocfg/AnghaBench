#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  format2bits ;
struct TYPE_4__ {unsigned int audio_format; unsigned char format_bits; } ;
typedef  TYPE_1__ ad1848_port_info ;
struct TYPE_5__ {size_t model; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_6__ {scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
#define  AFMT_A_LAW 136 
#define  AFMT_IMA_ADPCM 135 
#define  AFMT_MU_LAW 134 
#define  AFMT_S16_BE 133 
#define  AFMT_S16_LE 132 
#define  AFMT_S8 131 
#define  AFMT_U16_BE 130 
#define  AFMT_U16_LE 129 
#define  AFMT_U8 128 
 unsigned int* ad_format_mask ; 
 TYPE_3__** audio_devs ; 

__attribute__((used)) static unsigned int ad1848_set_bits(int dev, unsigned int arg)
{
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;
	ad1848_port_info *portc = (ad1848_port_info *) audio_devs[dev]->portc;

	static struct format_tbl
	{
		  int             format;
		  unsigned char   bits;
	}
	format2bits[] =
	{
		{
			0, 0
		}
		,
		{
			AFMT_MU_LAW, 1
		}
		,
		{
			AFMT_A_LAW, 3
		}
		,
		{
			AFMT_IMA_ADPCM, 5
		}
		,
		{
			AFMT_U8, 0
		}
		,
		{
			AFMT_S16_LE, 2
		}
		,
		{
			AFMT_S16_BE, 6
		}
		,
		{
			AFMT_S8, 0
		}
		,
		{
			AFMT_U16_LE, 0
		}
		,
		{
			AFMT_U16_BE, 0
		}
	};
	int i, n = sizeof(format2bits) / sizeof(struct format_tbl);

	if (arg == 0)
		return portc->audio_format;

	if (!(arg & ad_format_mask[devc->model]))
		arg = AFMT_U8;

	portc->audio_format = arg;

	for (i = 0; i < n; i++)
		if (format2bits[i].format == arg)
		{
			if ((portc->format_bits = format2bits[i].bits) == 0)
				return portc->audio_format = AFMT_U8;		/* Was not supported */

			return arg;
		}
	/* Still hanging here. Something must be terribly wrong */
	portc->format_bits = 0;
	return portc->audio_format = AFMT_U8;
}