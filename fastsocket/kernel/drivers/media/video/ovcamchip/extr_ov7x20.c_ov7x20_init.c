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
struct ovcamchip {struct ov7x20* spriv; scalar_t__ mono; } ;
struct ov7x20 {int auto_brt; int /*<<< orphan*/  auto_gain; int /*<<< orphan*/  auto_exp; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DFL_AUTO_EXP ; 
 int /*<<< orphan*/  DFL_AUTO_GAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 struct ov7x20* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ov_write_regvals (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regvals_init_7120 ; 
 int /*<<< orphan*/  regvals_init_7620 ; 

__attribute__((used)) static int ov7x20_init(struct i2c_client *c)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	struct ov7x20 *s;
	int rc;

	DDEBUG(4, &c->dev, "entered");

	if (ov->mono)
		rc = ov_write_regvals(c, regvals_init_7120);
	else
		rc = ov_write_regvals(c, regvals_init_7620);

	if (rc < 0)
		return rc;

	ov->spriv = s = kzalloc(sizeof *s, GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->auto_brt = 1;
	s->auto_exp = DFL_AUTO_EXP;
	s->auto_gain = DFL_AUTO_GAIN;

	return 0;
}