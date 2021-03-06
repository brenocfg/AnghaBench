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
struct fft_sample_tlv {int /*<<< orphan*/  length; } ;
struct ath_softc {int /*<<< orphan*/  rfs_chan_spec_scan; } ;

/* Variables and functions */
 int __be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_write (int /*<<< orphan*/ ,struct fft_sample_tlv*,int) ; 

void ath_debug_send_fft_sample(struct ath_softc *sc,
			       struct fft_sample_tlv *fft_sample_tlv)
{
	int length;
	if (!sc->rfs_chan_spec_scan)
		return;

	length = __be16_to_cpu(fft_sample_tlv->length) +
		 sizeof(*fft_sample_tlv);
	relay_write(sc->rfs_chan_spec_scan, fft_sample_tlv, length);
}