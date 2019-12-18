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

/* Variables and functions */

void construct_ctr_preload(
	unsigned char *ctr_preload,
	int a4_exists,
	int qc_exists,
	unsigned char *mpdu,
	unsigned char *pn_vector,
	int c)
{

	int i = 0;
	for (i=0; i<16; i++) ctr_preload[i] = 0x00;
	i = 0;

	ctr_preload[0] = 0x01;                                  /* flag */
	if (qc_exists && a4_exists) ctr_preload[1] = mpdu[30] & 0x0f;   /* QoC_Control  */
	if (qc_exists && !a4_exists) ctr_preload[1] = mpdu[24] & 0x0f;

	for (i = 2; i < 8; i++)
		ctr_preload[i] = mpdu[i + 8];                       /* ctr_preload[2:7] = A2[0:5] = mpdu[10:15] */
#ifdef CONSISTENT_PN_ORDER
	  for (i = 8; i < 14; i++)
			ctr_preload[i] =    pn_vector[i - 8];           /* ctr_preload[8:13] = PN[0:5] */
#else
	  for (i = 8; i < 14; i++)
			ctr_preload[i] =    pn_vector[13 - i];          /* ctr_preload[8:13] = PN[5:0] */
#endif
	ctr_preload[14] =  (unsigned char) (c / 256); // Ctr
	ctr_preload[15] =  (unsigned char) (c % 256);

}