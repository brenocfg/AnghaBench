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
struct pnp_card_device_id {TYPE_1__* devs; } ;
struct module {int /*<<< orphan*/  dev_table_buf; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_id ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 unsigned int PNP_MAX_DEVICES ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  device_id_check (int /*<<< orphan*/ ,char*,unsigned long,unsigned long const,void*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char toupper (char const) ; 

__attribute__((used)) static void do_pnp_card_entries(void *symval, unsigned long size,
				struct module *mod)
{
	const unsigned long id_size = sizeof(struct pnp_card_device_id);
	const unsigned int count = (size / id_size)-1;
	const struct pnp_card_device_id *cards = symval;
	unsigned int i;

	device_id_check(mod->name, "pnp", size, id_size, symval);

	for (i = 0; i < count; i++) {
		unsigned int j;
		const struct pnp_card_device_id *card = &cards[i];

		for (j = 0; j < PNP_MAX_DEVICES; j++) {
			const char *id = (char *)card->devs[j].id;
			int i2, j2;
			int dup = 0;

			if (!id[0])
				break;

			/* find duplicate, already added value */
			for (i2 = 0; i2 < i && !dup; i2++) {
				const struct pnp_card_device_id *card2 = &cards[i2];

				for (j2 = 0; j2 < PNP_MAX_DEVICES; j2++) {
					const char *id2 = (char *)card2->devs[j2].id;

					if (!id2[0])
						break;

					if (!strcmp(id, id2)) {
						dup = 1;
						break;
					}
				}
			}

			/* add an individual alias for every device entry */
			if (!dup) {
				char acpi_id[sizeof(card->devs[0].id)];
				int k;

				buf_printf(&mod->dev_table_buf,
					   "MODULE_ALIAS(\"pnp:d%s*\");\n", id);

				/* fix broken pnp bus lowercasing */
				for (k = 0; k < sizeof(acpi_id); k++)
					acpi_id[k] = toupper(id[k]);
				buf_printf(&mod->dev_table_buf,
					   "MODULE_ALIAS(\"acpi*:%s:*\");\n", acpi_id);
			}
		}
	}
}