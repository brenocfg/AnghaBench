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
struct ovcamchip_control {int value; int id; } ;
struct ovcamchip {struct ov6x20* spriv; } ;
struct ov6x20 {int bandfilt; int auto_brt; int auto_exp; int backlight; int mirror; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*,int,...) ; 
 int EPERM ; 
#define  OVCAMCHIP_CID_AUTOBRIGHT 138 
#define  OVCAMCHIP_CID_AUTOEXP 137 
#define  OVCAMCHIP_CID_BACKLIGHT 136 
#define  OVCAMCHIP_CID_BANDFILT 135 
#define  OVCAMCHIP_CID_BRIGHT 134 
#define  OVCAMCHIP_CID_CONT 133 
#define  OVCAMCHIP_CID_EXP 132 
#define  OVCAMCHIP_CID_FREQ 131 
#define  OVCAMCHIP_CID_HUE 130 
#define  OVCAMCHIP_CID_MIRROR 129 
#define  OVCAMCHIP_CID_SAT 128 
 int REG_BLUE ; 
 int REG_BRT ; 
 int REG_CNT ; 
 int REG_EXP ; 
 int REG_RED ; 
 int REG_SAT ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int ov_write (struct i2c_client*,int,int) ; 
 int ov_write_mask (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ov6x20_set_control(struct i2c_client *c,
			      struct ovcamchip_control *ctl)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	struct ov6x20 *s = ov->spriv;
	int rc;
	int v = ctl->value;

	switch (ctl->id) {
	case OVCAMCHIP_CID_CONT:
		rc = ov_write(c, REG_CNT, v >> 8);
		break;
	case OVCAMCHIP_CID_BRIGHT:
		rc = ov_write(c, REG_BRT, v >> 8);
		break;
	case OVCAMCHIP_CID_SAT:
		rc = ov_write(c, REG_SAT, v >> 8);
		break;
	case OVCAMCHIP_CID_HUE:
		rc = ov_write(c, REG_RED, 0xFF - (v >> 8));
		if (rc < 0)
			goto out;

		rc = ov_write(c, REG_BLUE, v >> 8);
		break;
	case OVCAMCHIP_CID_EXP:
		rc = ov_write(c, REG_EXP, v);
		break;
	case OVCAMCHIP_CID_FREQ:
	{
		int sixty = (v == 60);

		rc = ov_write(c, 0x2b, sixty?0xa8:0x28);
		if (rc < 0)
			goto out;

		rc = ov_write(c, 0x2a, sixty?0x84:0xa4);
		break;
	}
	case OVCAMCHIP_CID_BANDFILT:
		rc = ov_write_mask(c, 0x2d, v?0x04:0x00, 0x04);
		s->bandfilt = v;
		break;
	case OVCAMCHIP_CID_AUTOBRIGHT:
		rc = ov_write_mask(c, 0x2d, v?0x10:0x00, 0x10);
		s->auto_brt = v;
		break;
	case OVCAMCHIP_CID_AUTOEXP:
		rc = ov_write_mask(c, 0x13, v?0x01:0x00, 0x01);
		s->auto_exp = v;
		break;
	case OVCAMCHIP_CID_BACKLIGHT:
	{
		rc = ov_write_mask(c, 0x4e, v?0xe0:0xc0, 0xe0);
		if (rc < 0)
			goto out;

		rc = ov_write_mask(c, 0x29, v?0x08:0x00, 0x08);
		if (rc < 0)
			goto out;

		rc = ov_write_mask(c, 0x0e, v?0x80:0x00, 0x80);
		s->backlight = v;
		break;
	}
	case OVCAMCHIP_CID_MIRROR:
		rc = ov_write_mask(c, 0x12, v?0x40:0x00, 0x40);
		s->mirror = v;
		break;
	default:
		DDEBUG(2, &c->dev, "control not supported: %d", ctl->id);
		return -EPERM;
	}

out:
	DDEBUG(3, &c->dev, "id=%d, arg=%d, rc=%d", ctl->id, v, rc);
	return rc;
}