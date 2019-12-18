#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* i2eBordStrPtr ;
typedef  TYPE_3__* i2ChanStrPtr ;
struct TYPE_7__ {int BaudBase; int BaudDivisor; } ;
struct TYPE_5__ {scalar_t__* bid_value; } ;
struct TYPE_6__ {TYPE_1__ channelBtypes; scalar_t__ i2eChannelPtr; } ;

/* Variables and functions */
 int ABS_BIGGEST_BOX ; 
 int ABS_MAX_BOXES ; 
 scalar_t__ BID_HAS_654 (scalar_t__) ; 

__attribute__((used)) static inline void
set_baud_params(i2eBordStrPtr pB) 
{
	int i,j;
	i2ChanStrPtr  *pCh;

	pCh = (i2ChanStrPtr *) pB->i2eChannelPtr;

	for (i = 0; i < ABS_MAX_BOXES; i++) {
		if (pB->channelBtypes.bid_value[i]) {
			if (BID_HAS_654(pB->channelBtypes.bid_value[i])) {
				for (j = 0; j < ABS_BIGGEST_BOX; j++) {
					if (pCh[i*16+j] == NULL)
						break;
					(pCh[i*16+j])->BaudBase    = 921600;	// MAX for ST654
					(pCh[i*16+j])->BaudDivisor = 96;
				}
			} else {	// has cirrus cd1400
				for (j = 0; j < ABS_BIGGEST_BOX; j++) {
					if (pCh[i*16+j] == NULL)
						break;
					(pCh[i*16+j])->BaudBase    = 115200;	// MAX for CD1400
					(pCh[i*16+j])->BaudDivisor = 12;
				}
			}
		}
	}
}