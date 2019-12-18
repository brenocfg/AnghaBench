#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {TYPE_1__ dev; TYPE_2__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int udelay; int timeout; int /*<<< orphan*/  (* setscl ) (struct i810fb_i2c_chan*,int) ;int /*<<< orphan*/  (* setsda ) (struct i810fb_i2c_chan*,int) ;struct i810fb_i2c_chan* data; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; } ;
struct i810fb_i2c_chan {TYPE_4__* par; TYPE_5__ adapter; TYPE_2__ algo; } ;
struct TYPE_10__ {TYPE_3__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int i2c_bit_add_bus (TYPE_5__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_5__*,struct i810fb_i2c_chan*) ; 
 int /*<<< orphan*/  i810i2c_getscl ; 
 int /*<<< orphan*/  i810i2c_getsda ; 
 int /*<<< orphan*/  i810i2c_setscl (struct i810fb_i2c_chan*,int) ; 
 int /*<<< orphan*/  i810i2c_setsda (struct i810fb_i2c_chan*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (struct i810fb_i2c_chan*,int) ; 
 int /*<<< orphan*/  stub2 (struct i810fb_i2c_chan*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i810_setup_i2c_bus(struct i810fb_i2c_chan *chan, const char *name)
{
        int rc;

        strcpy(chan->adapter.name, name);
        chan->adapter.owner             = THIS_MODULE;
        chan->adapter.algo_data         = &chan->algo;
        chan->adapter.dev.parent        = &chan->par->dev->dev;
	chan->algo.setsda               = i810i2c_setsda;
	chan->algo.setscl               = i810i2c_setscl;
	chan->algo.getsda               = i810i2c_getsda;
	chan->algo.getscl               = i810i2c_getscl;
	chan->algo.udelay               = 10;
        chan->algo.timeout              = (HZ/2);
        chan->algo.data                 = chan;

        i2c_set_adapdata(&chan->adapter, chan);

        /* Raise SCL and SDA */
        chan->algo.setsda(chan, 1);
        chan->algo.setscl(chan, 1);
        udelay(20);

        rc = i2c_bit_add_bus(&chan->adapter);

        if (rc == 0)
                dev_dbg(&chan->par->dev->dev, "I2C bus %s registered.\n",name);
        else {
                dev_warn(&chan->par->dev->dev, "Failed to register I2C bus "
			 "%s.\n", name);
		chan->par = NULL;
	}

        return rc;
}