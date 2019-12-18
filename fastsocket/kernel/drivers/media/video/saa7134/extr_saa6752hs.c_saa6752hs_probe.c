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
struct v4l2_subdev {int dummy; } ;
struct saa6752hs_state {int revision; int has_ac3; scalar_t__ standard; int /*<<< orphan*/  params; int /*<<< orphan*/  chip; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_IDENT_SAA6752HS ; 
 int /*<<< orphan*/  V4L2_IDENT_SAA6752HS_AC3 ; 
 int /*<<< orphan*/  i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  i2c_master_send (struct i2c_client*,int*,int) ; 
 struct saa6752hs_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_defaults ; 
 int /*<<< orphan*/  saa6752hs_ops ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,...) ; 

__attribute__((used)) static int saa6752hs_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct saa6752hs_state *h = kzalloc(sizeof(*h), GFP_KERNEL);
	struct v4l2_subdev *sd;
	u8 addr = 0x13;
	u8 data[12];

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
	if (h == NULL)
		return -ENOMEM;
	sd = &h->sd;
	v4l2_i2c_subdev_init(sd, client, &saa6752hs_ops);

	i2c_master_send(client, &addr, 1);
	i2c_master_recv(client, data, sizeof(data));
	h->chip = V4L2_IDENT_SAA6752HS;
	h->revision = (data[8] << 8) | data[9];
	h->has_ac3 = 0;
	if (h->revision == 0x0206) {
		h->chip = V4L2_IDENT_SAA6752HS_AC3;
		h->has_ac3 = 1;
		v4l_info(client, "support AC-3\n");
	}
	h->params = param_defaults;
	h->standard = 0; /* Assume 625 input lines */
	return 0;
}