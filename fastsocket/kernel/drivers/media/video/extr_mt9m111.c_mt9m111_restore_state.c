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
struct mt9m111 {int /*<<< orphan*/  autowhitebalance; int /*<<< orphan*/  autoexposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  rect; TYPE_1__* fmt; int /*<<< orphan*/  context; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M111_RMB_MIRROR_COLS ; 
 int /*<<< orphan*/  MT9M111_RMB_MIRROR_ROWS ; 
 int /*<<< orphan*/  mt9m111_set_autoexposure (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_autowhitebalance (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_context (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_flip (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_global_gain (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_pixfmt (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_setup_rect (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_restore_state(struct i2c_client *client)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);

	mt9m111_set_context(client, mt9m111->context);
	mt9m111_set_pixfmt(client, mt9m111->fmt->code);
	mt9m111_setup_rect(client, &mt9m111->rect);
	mt9m111_set_flip(client, mt9m111->hflip, MT9M111_RMB_MIRROR_COLS);
	mt9m111_set_flip(client, mt9m111->vflip, MT9M111_RMB_MIRROR_ROWS);
	mt9m111_set_global_gain(client, mt9m111->gain);
	mt9m111_set_autoexposure(client, mt9m111->autoexposure);
	mt9m111_set_autowhitebalance(client, mt9m111->autowhitebalance);
	return 0;
}