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

/* Variables and functions */
 int CHUNKSIZE ; 
 int /*<<< orphan*/  IR_ARG_ASCII ; 
 int /*<<< orphan*/  IR_ARG_INT ; 
 int get_unaligned_be32 (char*) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
scdrv_parse_event(char *event, int *src, int *code, int *esp_code, char *desc)
{
	char *desc_end;

	/* record event source address */
	*src = get_unaligned_be32(event);
	event += 4; 			/* move on to event code */

	/* record the system controller's event code */
	*code = get_unaligned_be32(event);
	event += 4;			/* move on to event arguments */

	/* how many arguments are in the packet? */
	if (*event++ != 2) {
		/* if not 2, give up */
		return -1;
	}

	/* parse out the ESP code */
	if (*event++ != IR_ARG_INT) {
		/* not an integer argument, so give up */
		return -1;
	}
	*esp_code = get_unaligned_be32(event);
	event += 4;

	/* parse out the event description */
	if (*event++ != IR_ARG_ASCII) {
		/* not an ASCII string, so give up */
		return -1;
	}
	event[CHUNKSIZE-1] = '\0';	/* ensure this string ends! */
	event += 2; 			/* skip leading CR/LF */
	desc_end = desc + sprintf(desc, "%s", event);

	/* strip trailing CR/LF (if any) */
	for (desc_end--;
	     (desc_end != desc) && ((*desc_end == 0xd) || (*desc_end == 0xa));
	     desc_end--) {
		*desc_end = '\0';
	}

	return 0;
}