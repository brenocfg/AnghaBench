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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_initialize (struct i2c_client*) ; 
 int /*<<< orphan*/  cx23885_initialize (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25836_initialize (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_initialize (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 scalar_t__ is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_reset(struct v4l2_subdev *sd, u32 val)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (is_cx2583x(state))
		cx25836_initialize(client);
	else if (is_cx2388x(state))
		cx23885_initialize(client);
	else if (is_cx231xx(state))
		cx231xx_initialize(client);
	else
		cx25840_initialize(client);
	return 0;
}