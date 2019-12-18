#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct request {int /*<<< orphan*/  errors; } ;
struct TYPE_3__ {int /*<<< orphan*/  tcntxt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * head; TYPE_1__ s; } ;
struct i2o_message {int /*<<< orphan*/ * body; TYPE_2__ u; } ;
struct i2o_controller {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  i2o_block_end_request (struct request*,int,int) ; 
 struct request* i2o_cntxt_list_get (struct i2o_controller*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_err (char*,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i2o_block_reply(struct i2o_controller *c, u32 m,
			   struct i2o_message *msg)
{
	struct request *req;
	int error = 0;

	req = i2o_cntxt_list_get(c, le32_to_cpu(msg->u.s.tcntxt));
	if (unlikely(!req)) {
		osm_err("NULL reply received!\n");
		return -1;
	}

	/*
	 *      Lets see what is cooking. We stuffed the
	 *      request in the context.
	 */

	if ((le32_to_cpu(msg->body[0]) >> 24) != 0) {
		u32 status = le32_to_cpu(msg->body[0]);
		/*
		 *      Device not ready means two things. One is that the
		 *      the thing went offline (but not a removal media)
		 *
		 *      The second is that you have a SuperTrak 100 and the
		 *      firmware got constipated. Unlike standard i2o card
		 *      setups the supertrak returns an error rather than
		 *      blocking for the timeout in these cases.
		 *
		 *      Don't stick a supertrak100 into cache aggressive modes
		 */

		osm_err("TID %03x error status: 0x%02x, detailed status: "
			"0x%04x\n", (le32_to_cpu(msg->u.head[1]) >> 12 & 0xfff),
			status >> 24, status & 0xffff);

		req->errors++;

		error = -EIO;
	}

	i2o_block_end_request(req, error, le32_to_cpu(msg->body[1]));

	return 1;
}