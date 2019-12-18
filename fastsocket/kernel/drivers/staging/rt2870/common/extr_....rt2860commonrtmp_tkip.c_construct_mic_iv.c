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

void construct_mic_iv(
	unsigned char *mic_iv,
	int qc_exists,
	int a4_exists,
	unsigned char *mpdu,
	unsigned int payload_length,
	unsigned char *pn_vector)
{
	int i;

	mic_iv[0] = 0x59;
	if (qc_exists && a4_exists)
		mic_iv[1] = mpdu[30] & 0x0f;    /* QoS_TC           */
	if (qc_exists && !a4_exists)
		mic_iv[1] = mpdu[24] & 0x0f;   /* mute bits 7-4    */
	if (!qc_exists)
		mic_iv[1] = 0x00;
	for (i = 2; i < 8; i++)
		mic_iv[i] = mpdu[i + 8];                    /* mic_iv[2:7] = A2[0:5] = mpdu[10:15] */
#ifdef CONSISTENT_PN_ORDER
		for (i = 8; i < 14; i++)
			mic_iv[i] = pn_vector[i - 8];           /* mic_iv[8:13] = PN[0:5] */
#else
		for (i = 8; i < 14; i++)
			mic_iv[i] = pn_vector[13 - i];          /* mic_iv[8:13] = PN[5:0] */
#endif
	i = (payload_length / 256);
	i = (payload_length % 256);
	mic_iv[14] = (unsigned char) (payload_length / 256);
	mic_iv[15] = (unsigned char) (payload_length % 256);

}