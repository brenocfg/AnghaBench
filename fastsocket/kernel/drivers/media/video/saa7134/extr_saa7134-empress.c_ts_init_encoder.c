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
typedef  int u32 ;
struct saa7134_dev {int board; int empress_started; } ;

/* Variables and functions */
#define  SAA7134_BOARD_BEHOLD_M6 130 
#define  SAA7134_BOARD_BEHOLD_M63 129 
#define  SAA7134_BOARD_BEHOLD_M6_EXTRA 128 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_reset_encoder (struct saa7134_dev*) ; 

__attribute__((used)) static int ts_init_encoder(struct saa7134_dev* dev)
{
	u32 leading_null_bytes = 0;

	/* If more cards start to need this, then this
	   should probably be added to the card definitions. */
	switch (dev->board) {
	case SAA7134_BOARD_BEHOLD_M6:
	case SAA7134_BOARD_BEHOLD_M63:
	case SAA7134_BOARD_BEHOLD_M6_EXTRA:
		leading_null_bytes = 1;
		break;
	}
	ts_reset_encoder(dev);
	saa_call_all(dev, core, init, leading_null_bytes);
	dev->empress_started = 1;
	return 0;
}