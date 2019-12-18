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
struct of_device {int /*<<< orphan*/  node; } ;
struct bbc_i2c_client {int /*<<< orphan*/  address; int /*<<< orphan*/  bus; struct of_device* op; struct bbc_i2c_bus* bp; } ;
struct bbc_i2c_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  claim_device (struct bbc_i2c_bus*,struct of_device*) ; 
 int /*<<< orphan*/  kfree (struct bbc_i2c_client*) ; 
 struct bbc_i2c_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

struct bbc_i2c_client *bbc_i2c_attach(struct bbc_i2c_bus *bp, struct of_device *op)
{
	struct bbc_i2c_client *client;
	const u32 *reg;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return NULL;
	client->bp = bp;
	client->op = op;

	reg = of_get_property(op->node, "reg", NULL);
	if (!reg) {
		kfree(client);
		return NULL;
	}

	client->bus = reg[0];
	client->address = reg[1];

	claim_device(bp, op);

	return client;
}