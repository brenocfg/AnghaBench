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
struct ms_id_register {int /*<<< orphan*/  if_mode; int /*<<< orphan*/  class; int /*<<< orphan*/  category; int /*<<< orphan*/  type; } ;
struct memstick_request {int /*<<< orphan*/  data; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; int /*<<< orphan*/  category; int /*<<< orphan*/  type; int /*<<< orphan*/  match_flags; } ;
struct memstick_dev {int /*<<< orphan*/  mrq_complete; int /*<<< orphan*/  dev; TYPE_1__ id; struct memstick_request current_mrq; } ;
typedef  int /*<<< orphan*/  id_reg ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MEMSTICK_MATCH_ALL ; 
 int /*<<< orphan*/  MS_TPC_READ_REG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ms_id_register*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int h_memstick_read_dev_id(struct memstick_dev *card,
				  struct memstick_request **mrq)
{
	struct ms_id_register id_reg;

	if (!(*mrq)) {
		memstick_init_req(&card->current_mrq, MS_TPC_READ_REG, NULL,
				  sizeof(struct ms_id_register));
		*mrq = &card->current_mrq;
		return 0;
	} else {
		if (!(*mrq)->error) {
			memcpy(&id_reg, (*mrq)->data, sizeof(id_reg));
			card->id.match_flags = MEMSTICK_MATCH_ALL;
			card->id.type = id_reg.type;
			card->id.category = id_reg.category;
			card->id.class = id_reg.class;
			dev_dbg(&card->dev, "if_mode = %02x\n", id_reg.if_mode);
		}
		complete(&card->mrq_complete);
		return -EAGAIN;
	}
}