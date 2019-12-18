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
struct ovcamchip {struct ov7x20* spriv; } ;
struct ov7x20 {int auto_brt; int auto_exp; int bandfilt; int backlight; int mirror; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*,int,...) ; 
 int EBUSY ; 
 int EPERM ; 
#define  OVCAMCHIP_CID_AUTOBRIGHT 137 
#define  OVCAMCHIP_CID_AUTOEXP 136 
#define  OVCAMCHIP_CID_BACKLIGHT 135 
#define  OVCAMCHIP_CID_BANDFILT 134 
#define  OVCAMCHIP_CID_BRIGHT 133 
#define  OVCAMCHIP_CID_CONT 132 
#define  OVCAMCHIP_CID_EXP 131 
#define  OVCAMCHIP_CID_FREQ 130 
#define  OVCAMCHIP_CID_MIRROR 129 
#define  OVCAMCHIP_CID_SAT 128 
 int REG_BRT ; 
 int REG_EXP ; 
 int REG_SAT ; 
 int* ctab ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int ov_write (struct i2c_client*,int,int) ; 
 int ov_write_mask (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ov7x20_set_v4l1_control(struct i2c_client *c,
				   struct ovcamchip_control *ctl)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	struct ov7x20 *s = ov->spriv;
	int rc;
	int v = ctl->value;

	switch (ctl->id) {
	case OVCAMCHIP_CID_CONT:
	{
		/* Use Y gamma control instead. Bit 0 enables it. */
		rc = ov_write(c, 0x64, ctab[v >> 12]);
		break;
	}
	case OVCAMCHIP_CID_BRIGHT:
		/* 7620 doesn't like manual changes when in auto mode */
		if (!s->auto_brt)
			rc = ov_write(c, REG_BRT, v >> 8);
		else
			rc = 0;
		break;
	case OVCAMCHIP_CID_SAT:
		rc = ov_write(c, REG_SAT, v >> 8);
		break;
	case OVCAMCHIP_CID_EXP:
		if (!s->auto_exp)
			rc = ov_write(c, REG_EXP, v);
		else
			rc = -EBUSY;
		break;
	case OVCAMCHIP_CID_FREQ:
	{
		int sixty = (v == 60);

		rc = ov_write_mask(c, 0x2a, sixty?0x00:0x80, 0x80);
		if (rc < 0)
			goto out;

		rc = ov_write(c, 0x2b, sixty?0x00:0xac);
		if (rc < 0)
			goto out;

		rc = ov_write_mask(c, 0x76, 0x01, 0x01);
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
		rc = ov_write_mask(c, 0x68, v?0xe0:0xc0, 0xe0);
		if (rc < 0)
			goto out;

		rc = ov_write_mask(c, 0x29, v?0x08:0x00, 0x08);
		if (rc < 0)
			goto out;

		rc = ov_write_mask(c, 0x28, v?0x02:0x00, 0x02);
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