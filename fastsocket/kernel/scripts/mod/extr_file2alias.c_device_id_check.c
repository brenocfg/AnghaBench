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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ cross_build ; 
 int /*<<< orphan*/  fatal (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void device_id_check(const char *modname, const char *device_id,
			    unsigned long size, unsigned long id_size,
			    void *symval)
{
	int i;

	if (size % id_size || size < id_size) {
		if (cross_build != 0)
			return;
		fatal("%s: sizeof(struct %s_device_id)=%lu is not a modulo "
		      "of the size of section __mod_%s_device_table=%lu.\n"
		      "Fix definition of struct %s_device_id "
		      "in mod_devicetable.h\n",
		      modname, device_id, id_size, device_id, size, device_id);
	}
	/* Verify last one is a terminator */
	for (i = 0; i < id_size; i++ ) {
		if (*(uint8_t*)(symval+size-id_size+i)) {
			fprintf(stderr,"%s: struct %s_device_id is %lu bytes.  "
				"The last of %lu is:\n",
				modname, device_id, id_size, size / id_size);
			for (i = 0; i < id_size; i++ )
				fprintf(stderr,"0x%02x ",
					*(uint8_t*)(symval+size-id_size+i) );
			fprintf(stderr,"\n");
			fatal("%s: struct %s_device_id is not terminated "
				"with a NULL entry!\n", modname, device_id);
		}
	}
}