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
typedef  char uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  engine ;
struct TYPE_2__ {size_t engine_len; int* engine_id; int engine_boots; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int SNMP_ENGINE_ID_SIZ ; 
 char* engine_file ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 TYPE_1__ snmpd_engine ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
set_snmpd_engine(void)
{
	FILE *fp;
	uint32_t i;
	uint8_t *cptr, engine[2 * SNMP_ENGINE_ID_SIZ + 2];
	uint8_t myengine[2 * SNMP_ENGINE_ID_SIZ + 2];

	if (engine_file[0] == '\0')
		return (-1);

	cptr = myengine;
	for (i = 0; i < snmpd_engine.engine_len; i++)
		cptr += sprintf(cptr, "%.2x", snmpd_engine.engine_id[i]);
	*cptr++ = '\n';
	*cptr++ = '\0';

	if ((fp = fopen(engine_file, "r+")) != NULL) {
		if (fgets(engine, sizeof(engine) - 1, fp) == NULL ||
		    fscanf(fp, "%u",  &snmpd_engine.engine_boots) <= 0) {
			fclose(fp);
			goto save_boots;
		}

		fclose(fp);
		if (strcmp(myengine, engine) != 0)
			snmpd_engine.engine_boots = 1;
		else
			snmpd_engine.engine_boots++;
	} else if (errno != ENOENT)
		return (-1);

save_boots:
	if ((fp = fopen(engine_file, "w+")) == NULL)
		return (-1);
	fprintf(fp, "%s%u\n", myengine, snmpd_engine.engine_boots);
	fclose(fp);

	return (0);
}