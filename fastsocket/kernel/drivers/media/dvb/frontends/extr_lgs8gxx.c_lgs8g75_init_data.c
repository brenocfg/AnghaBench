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
typedef  int u8 ;
struct lgs8gxx_state {TYPE_1__* i2c; } ;
struct firmware {int size; int* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lgs8g75_init_data(struct lgs8gxx_state *priv)
{
	const struct firmware *fw;
	int rc;
	int i;

	rc = request_firmware(&fw, "lgs8g75.fw", &priv->i2c->dev);
	if (rc)
		return rc;

	lgs8gxx_write_reg(priv, 0xC6, 0x40);

	lgs8gxx_write_reg(priv, 0x3D, 0x04);
	lgs8gxx_write_reg(priv, 0x39, 0x00);

	lgs8gxx_write_reg(priv, 0x3A, 0x00);
	lgs8gxx_write_reg(priv, 0x38, 0x00);
	lgs8gxx_write_reg(priv, 0x3B, 0x00);
	lgs8gxx_write_reg(priv, 0x38, 0x00);

	for (i = 0; i < fw->size; i++) {
		lgs8gxx_write_reg(priv, 0x38, 0x00);
		lgs8gxx_write_reg(priv, 0x3A, (u8)(i&0xff));
		lgs8gxx_write_reg(priv, 0x3B, (u8)(i>>8));
		lgs8gxx_write_reg(priv, 0x3C, fw->data[i]);
	}

	lgs8gxx_write_reg(priv, 0x38, 0x00);

	release_firmware(fw);
	return 0;
}