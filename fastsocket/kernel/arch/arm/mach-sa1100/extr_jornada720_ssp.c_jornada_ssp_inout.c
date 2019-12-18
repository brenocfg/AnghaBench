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
typedef  int u8 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int TXDUMMY ; 
 int jornada_ssp_byte (int) ; 

int jornada_ssp_inout(u8 byte)
{
	int ret, i;

	/* true means command byte */
	if (byte != TXDUMMY) {
		ret = jornada_ssp_byte(byte);
		/* Proper return to commands is TxDummy */
		if (ret != TXDUMMY) {
			for (i = 0; i < 256; i++)/* flushing bus */
				if (jornada_ssp_byte(TXDUMMY) == -1)
					break;
			return -ETIMEDOUT;
		}
	} else /* Exchange TxDummy for data */
		ret = jornada_ssp_byte(TXDUMMY);

	return ret;
}