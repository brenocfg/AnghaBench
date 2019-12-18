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
typedef  scalar_t__ u16 ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct dvb_frontend {struct bcm3510_state* demodulator_priv; } ;
struct bcm3510_state {TYPE_1__* config; } ;
struct TYPE_2__ {int (* request_firmware ) (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCM3510_DEFAULT_FIRMWARE ; 
 int bcm3510_write_ram (struct bcm3510_state*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int stub1 (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm3510_download_firmware(struct dvb_frontend* fe)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	const struct firmware *fw;
	u16 addr,len;
	const u8 *b;
	int ret,i;

	deb_info("requesting firmware\n");
	if ((ret = st->config->request_firmware(fe, &fw, BCM3510_DEFAULT_FIRMWARE)) < 0) {
		err("could not load firmware (%s): %d",BCM3510_DEFAULT_FIRMWARE,ret);
		return ret;
	}
	deb_info("got firmware: %zd\n",fw->size);

	b = fw->data;
	for (i = 0; i < fw->size;) {
		addr = le16_to_cpu( *( (u16 *)&b[i] ) );
		len  = le16_to_cpu( *( (u16 *)&b[i+2] ) );
		deb_info("firmware chunk, addr: 0x%04x, len: 0x%04x, total length: 0x%04zx\n",addr,len,fw->size);
		if ((ret = bcm3510_write_ram(st,addr,&b[i+4],len)) < 0) {
			err("firmware download failed: %d\n",ret);
			return ret;
		}
		i += 4 + len;
	}
	release_firmware(fw);
	deb_info("firmware download successfully completed\n");
	return 0;
}