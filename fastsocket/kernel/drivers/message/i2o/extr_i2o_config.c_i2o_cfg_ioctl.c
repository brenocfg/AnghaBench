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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  I2OEVTGET 139 
#define  I2OEVTREG 138 
#define  I2OGETIOPS 137 
#define  I2OHRTGET 136 
#define  I2OLCTGET 135 
#define  I2OPARMGET 134 
#define  I2OPARMSET 133 
#define  I2OPASSTHRU 132 
#define  I2OSWDEL 131 
#define  I2OSWDL 130 
#define  I2OSWUL 129 
#define  I2OVALIDATE 128 
 int i2o_cfg_evt_get (unsigned long,struct file*) ; 
 int i2o_cfg_evt_reg (unsigned long,struct file*) ; 
 int i2o_cfg_gethrt (unsigned long) ; 
 int i2o_cfg_getiops (unsigned long) ; 
 int i2o_cfg_getlct (unsigned long) ; 
 int i2o_cfg_parms (unsigned long,int const) ; 
 int i2o_cfg_passthru (unsigned long) ; 
 int i2o_cfg_swdel (unsigned long) ; 
 int i2o_cfg_swdl (unsigned long) ; 
 int i2o_cfg_swul (unsigned long) ; 
 int i2o_cfg_validate (unsigned long) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 

__attribute__((used)) static int i2o_cfg_ioctl(struct inode *inode, struct file *fp, unsigned int cmd,
			 unsigned long arg)
{
	int ret;

	switch (cmd) {
	case I2OGETIOPS:
		ret = i2o_cfg_getiops(arg);
		break;

	case I2OHRTGET:
		ret = i2o_cfg_gethrt(arg);
		break;

	case I2OLCTGET:
		ret = i2o_cfg_getlct(arg);
		break;

	case I2OPARMSET:
		ret = i2o_cfg_parms(arg, I2OPARMSET);
		break;

	case I2OPARMGET:
		ret = i2o_cfg_parms(arg, I2OPARMGET);
		break;

	case I2OSWDL:
		ret = i2o_cfg_swdl(arg);
		break;

	case I2OSWUL:
		ret = i2o_cfg_swul(arg);
		break;

	case I2OSWDEL:
		ret = i2o_cfg_swdel(arg);
		break;

	case I2OVALIDATE:
		ret = i2o_cfg_validate(arg);
		break;

	case I2OEVTREG:
		ret = i2o_cfg_evt_reg(arg, fp);
		break;

	case I2OEVTGET:
		ret = i2o_cfg_evt_get(arg, fp);
		break;

#ifdef CONFIG_I2O_EXT_ADAPTEC
	case I2OPASSTHRU:
		ret = i2o_cfg_passthru(arg);
		break;
#endif

	default:
		osm_debug("unknown ioctl called!\n");
		ret = -EINVAL;
	}

	return ret;
}