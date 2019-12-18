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
struct ovcamchip {struct ov6x30* spriv; } ;
struct ov6x30 {int auto_brt; int auto_exp; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 struct ov6x30* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ov_write_regvals (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regvals_init_6x30 ; 

__attribute__((used)) static int ov6x30_init(struct i2c_client *c)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	struct ov6x30 *s;
	int rc;

	DDEBUG(4, &c->dev, "entered");

	rc = ov_write_regvals(c, regvals_init_6x30);
	if (rc < 0)
		return rc;

	ov->spriv = s = kzalloc(sizeof *s, GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->auto_brt = 1;
	s->auto_exp = 1;

	return rc;
}