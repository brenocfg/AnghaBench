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
struct ovcamchip_control {int id; unsigned char value; } ;
struct ovcamchip {struct ov76be* spriv; } ;
struct ov76be {unsigned char bandfilt; unsigned char auto_brt; unsigned char auto_exp; unsigned char mirror; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*,int,...) ; 
 int EPERM ; 
#define  OVCAMCHIP_CID_AUTOBRIGHT 134 
#define  OVCAMCHIP_CID_AUTOEXP 133 
#define  OVCAMCHIP_CID_BANDFILT 132 
#define  OVCAMCHIP_CID_BRIGHT 131 
#define  OVCAMCHIP_CID_EXP 130 
#define  OVCAMCHIP_CID_MIRROR 129 
#define  OVCAMCHIP_CID_SAT 128 
 int /*<<< orphan*/  REG_BRT ; 
 int /*<<< orphan*/  REG_EXP ; 
 int /*<<< orphan*/  REG_SAT ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int ov_read (struct i2c_client*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov76be_get_control(struct i2c_client *c,
			      struct ovcamchip_control *ctl)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	struct ov76be *s = ov->spriv;
	int rc = 0;
	unsigned char val = 0;

	switch (ctl->id) {
	case OVCAMCHIP_CID_BRIGHT:
		rc = ov_read(c, REG_BRT, &val);
		ctl->value = val << 8;
		break;
	case OVCAMCHIP_CID_SAT:
		rc = ov_read(c, REG_SAT, &val);
		ctl->value = val << 8;
		break;
	case OVCAMCHIP_CID_EXP:
		rc = ov_read(c, REG_EXP, &val);
		ctl->value = val;
		break;
	case OVCAMCHIP_CID_BANDFILT:
		ctl->value = s->bandfilt;
		break;
	case OVCAMCHIP_CID_AUTOBRIGHT:
		ctl->value = s->auto_brt;
		break;
	case OVCAMCHIP_CID_AUTOEXP:
		ctl->value = s->auto_exp;
		break;
	case OVCAMCHIP_CID_MIRROR:
		ctl->value = s->mirror;
		break;
	default:
		DDEBUG(2, &c->dev, "control not supported: %d", ctl->id);
		return -EPERM;
	}

	DDEBUG(3, &c->dev, "id=%d, arg=%d, rc=%d", ctl->id, ctl->value, rc);
	return rc;
}