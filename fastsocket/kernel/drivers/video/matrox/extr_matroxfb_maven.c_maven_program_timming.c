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
struct mavenregs {scalar_t__ mode; } ;
struct maven_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LR (int) ; 
 int /*<<< orphan*/  LRP (int) ; 
 scalar_t__ MATROXFB_OUTPUT_MODE_MONITOR ; 
 int /*<<< orphan*/  maven_init_TV (struct i2c_client*,struct mavenregs const*) ; 

__attribute__((used)) static int maven_program_timming(struct maven_data* md,
		const struct mavenregs* m) {
	struct i2c_client *c = md->client;

	if (m->mode == MATROXFB_OUTPUT_MODE_MONITOR) {
		LR(0x80);
		LR(0x81);
		LR(0x82);

		LR(0xB3);
		LR(0x94);

		LRP(0x96);
		LRP(0x98);
		LRP(0x9A);
		LRP(0x9C);
		LRP(0x9E);
		LRP(0xA0);
		LRP(0xA2);
		LRP(0xA4);
		LRP(0xA6);
		LRP(0xA8);
		LRP(0xAA);
		LRP(0xAC);
		LRP(0xAE);

		LR(0xB0);	/* output: monitor */
		LR(0xB1);	/* ??? */
		LR(0x8C);	/* must be set... */
		LR(0x8D);	/* defaults to 0x10: test signal */
		LR(0xB9);	/* defaults to 0x2C: too bright */
		LR(0xBF);	/* makes picture stable */
	} else {
		maven_init_TV(c, m);
	}
	return 0;
}