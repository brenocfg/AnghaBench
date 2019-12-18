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
typedef  int /*<<< orphan*/  u8 ;
struct cx231xx {int dummy; } ;
typedef  enum AUDIO_INPUT { ____Placeholder_AUDIO_INPUT } AUDIO_INPUT ;
struct TYPE_2__ {int amux; } ;

/* Variables and functions */
 int AUDIO_INPUT_LINE ; 
 int AUDIO_INPUT_TUNER_TV ; 
#define  CX231XX_AMUX_LINE_IN 129 
#define  CX231XX_AMUX_VIDEO 128 
 TYPE_1__* INPUT (int /*<<< orphan*/ ) ; 
 int cx231xx_i2s_blk_set_audio_input (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int cx231xx_set_audio_decoder_input (struct cx231xx*,int) ; 

int cx231xx_set_audio_input(struct cx231xx *dev, u8 input)
{
	int status = 0;
	enum AUDIO_INPUT ainput = AUDIO_INPUT_LINE;

	switch (INPUT(input)->amux) {
	case CX231XX_AMUX_VIDEO:
		ainput = AUDIO_INPUT_TUNER_TV;
		break;
	case CX231XX_AMUX_LINE_IN:
		status = cx231xx_i2s_blk_set_audio_input(dev, input);
		ainput = AUDIO_INPUT_LINE;
		break;
	default:
		break;
	}

	status = cx231xx_set_audio_decoder_input(dev, ainput);

	return status;
}