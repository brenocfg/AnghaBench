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
typedef  int u32 ;
struct msp_state {int route_in; scalar_t__ has_scart2_out; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp34xxg_set_source (struct i2c_client*,int,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msp34xxg_set_sources(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	u32 in = state->route_in;

	msp34xxg_set_source(client, 0x0008, (in >> 4) & 0xf);
	/* quasi-peak detector is set to same input as the loudspeaker (MAIN) */
	msp34xxg_set_source(client, 0x000c, (in >> 4) & 0xf);
	msp34xxg_set_source(client, 0x0009, (in >> 8) & 0xf);
	msp34xxg_set_source(client, 0x000a, (in >> 12) & 0xf);
	if (state->has_scart2_out)
		msp34xxg_set_source(client, 0x0041, (in >> 16) & 0xf);
	msp34xxg_set_source(client, 0x000b, (in >> 20) & 0xf);
}