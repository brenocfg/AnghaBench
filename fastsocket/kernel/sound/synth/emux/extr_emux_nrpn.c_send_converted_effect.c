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
struct snd_midi_channel {int dummy; } ;
struct snd_emux_port {int dummy; } ;
struct nrpn_conv_table {int control; int (* convert ) (int) ;int /*<<< orphan*/  effect; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emux_send_effect (struct snd_emux_port*,struct snd_midi_channel*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (int) ; 

__attribute__((used)) static int send_converted_effect(struct nrpn_conv_table *table, int num_tables,
				 struct snd_emux_port *port,
				 struct snd_midi_channel *chan,
				 int type, int val, int mode)
{
	int i, cval;
	for (i = 0; i < num_tables; i++) {
		if (table[i].control == type) {
			cval = table[i].convert(val);
			snd_emux_send_effect(port, chan, table[i].effect,
					     cval, mode);
			return 1;
		}
	}
	return 0;
}