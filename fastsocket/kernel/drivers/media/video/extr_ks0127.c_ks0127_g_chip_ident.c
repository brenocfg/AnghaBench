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
struct v4l2_subdev {int dummy; } ;
struct v4l2_dbg_chip_ident {int dummy; } ;
struct ks0127 {int /*<<< orphan*/  ident; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ks0127* to_ks0127 (struct v4l2_subdev*) ; 
 int v4l2_chip_ident_i2c_client (struct i2c_client*,struct v4l2_dbg_chip_ident*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ks0127_g_chip_ident(struct v4l2_subdev *sd, struct v4l2_dbg_chip_ident *chip)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ks0127 *ks = to_ks0127(sd);

	return v4l2_chip_ident_i2c_client(client, chip, ks->ident, 0);
}