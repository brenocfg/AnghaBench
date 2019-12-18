#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {void** head; } ;
struct i2o_message {void** body; TYPE_2__ u; } ;
struct TYPE_9__ {int len; int phys; TYPE_3__* virt; } ;
struct i2o_controller {int /*<<< orphan*/  name; TYPE_4__ hrt; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int num_entries; int entry_len; } ;
typedef  TYPE_3__ i2o_hrt ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int ADAPTER_TID ; 
 int EBUSY ; 
 int ENOMEM ; 
 int HOST_TID ; 
 int I2O_CMD_HRT_GET ; 
 int I2O_HRT_GET_TRIES ; 
 int /*<<< orphan*/  I2O_TIMEOUT_MESSAGE_GET ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int PTR_ERR (struct i2o_message*) ; 
 int SGL_OFFSET_4 ; 
 int SIX_WORD_MSG_SIZE ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ i2o_dma_realloc (struct device*,TYPE_4__*,int) ; 
 struct i2o_message* i2o_msg_get_wait (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int i2o_msg_post_wait_mem (struct i2o_controller*,struct i2o_message*,int,TYPE_4__*) ; 
 int i2o_parse_hrt (struct i2o_controller*) ; 
 int /*<<< orphan*/  osm_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2o_hrt_get(struct i2o_controller *c)
{
	int rc;
	int i;
	i2o_hrt *hrt = c->hrt.virt;
	u32 size = sizeof(i2o_hrt);
	struct device *dev = &c->pdev->dev;

	for (i = 0; i < I2O_HRT_GET_TRIES; i++) {
		struct i2o_message *msg;

		msg = i2o_msg_get_wait(c, I2O_TIMEOUT_MESSAGE_GET);
		if (IS_ERR(msg))
			return PTR_ERR(msg);

		msg->u.head[0] = cpu_to_le32(SIX_WORD_MSG_SIZE | SGL_OFFSET_4);
		msg->u.head[1] =
		    cpu_to_le32(I2O_CMD_HRT_GET << 24 | HOST_TID << 12 |
				ADAPTER_TID);
		msg->body[0] = cpu_to_le32(0xd0000000 | c->hrt.len);
		msg->body[1] = cpu_to_le32(c->hrt.phys);

		rc = i2o_msg_post_wait_mem(c, msg, 20, &c->hrt);

		if (rc < 0) {
			osm_err("%s: Unable to get HRT (status=%#x)\n", c->name,
				-rc);
			return rc;
		}

		size = hrt->num_entries * hrt->entry_len << 2;
		if (size > c->hrt.len) {
			if (i2o_dma_realloc(dev, &c->hrt, size))
				return -ENOMEM;
			else
				hrt = c->hrt.virt;
		} else
			return i2o_parse_hrt(c);
	}

	osm_err("%s: Unable to get HRT after %d tries, giving up\n", c->name,
		I2O_HRT_GET_TRIES);

	return -EBUSY;
}