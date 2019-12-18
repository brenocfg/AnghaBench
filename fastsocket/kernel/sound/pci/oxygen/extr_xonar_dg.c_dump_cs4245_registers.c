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
struct snd_info_buffer {int dummy; } ;
struct oxygen {struct dg* model_data; } ;
struct dg {int /*<<< orphan*/ * cs4245_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dump_cs4245_registers(struct oxygen *chip,
				  struct snd_info_buffer *buffer)
{
	struct dg *data = chip->model_data;
	unsigned int i;

	snd_iprintf(buffer, "\nCS4245:");
	for (i = 1; i <= 0x10; ++i)
		snd_iprintf(buffer, " %02x", data->cs4245_regs[i]);
	snd_iprintf(buffer, "\n");
}