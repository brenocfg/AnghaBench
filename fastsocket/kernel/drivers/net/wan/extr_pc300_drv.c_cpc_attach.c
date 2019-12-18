#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ chan; } ;
typedef  TYPE_3__ pc300dev_t ;
struct TYPE_9__ {unsigned short encoding; unsigned short parity; } ;
struct TYPE_11__ {TYPE_2__ proto_settings; } ;
typedef  TYPE_4__ pc300chconf_t ;
struct TYPE_12__ {int /*<<< orphan*/  conf; scalar_t__ card; } ;
typedef  TYPE_5__ pc300ch_t ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_13__ {TYPE_1__ hw; } ;
typedef  TYPE_6__ pc300_t ;
struct TYPE_14__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short ENCODING_FM_MARK ; 
 unsigned short ENCODING_FM_SPACE ; 
 unsigned short ENCODING_NRZ ; 
 unsigned short ENCODING_NRZI ; 
 unsigned short PARITY_CRC16_PR0 ; 
 unsigned short PARITY_CRC16_PR1 ; 
 unsigned short PARITY_CRC16_PR1_CCITT ; 
 unsigned short PARITY_CRC32_PR1_CCITT ; 
 unsigned short PARITY_NONE ; 
 scalar_t__ PC300_TE ; 
 TYPE_7__* dev_to_hdlc (struct net_device*) ; 

__attribute__((used)) static int cpc_attach(struct net_device *dev, unsigned short encoding,
		      unsigned short parity)
{
	pc300dev_t *d = (pc300dev_t *)dev_to_hdlc(dev)->priv;
	pc300ch_t *chan = (pc300ch_t *)d->chan;
	pc300_t *card = (pc300_t *)chan->card;
	pc300chconf_t *conf = (pc300chconf_t *)&chan->conf;

	if (card->hw.type == PC300_TE) {
		if (encoding != ENCODING_NRZ && encoding != ENCODING_NRZI) {
			return -EINVAL;
		}
	} else {
		if (encoding != ENCODING_NRZ && encoding != ENCODING_NRZI &&
		    encoding != ENCODING_FM_MARK && encoding != ENCODING_FM_SPACE) {
			/* Driver doesn't support ENCODING_MANCHESTER yet */
			return -EINVAL;
		}
	}

	if (parity != PARITY_NONE && parity != PARITY_CRC16_PR0 &&
	    parity != PARITY_CRC16_PR1 && parity != PARITY_CRC32_PR1_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT) {
		return -EINVAL;
	}

	conf->proto_settings.encoding = encoding;
	conf->proto_settings.parity = parity;
	return 0;
}