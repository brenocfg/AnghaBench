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
struct gtco {int max_X; int min_X; int max_Y; int min_Y; int maxtilt_X; int mintilt_X; int maxtilt_Y; int mintilt_Y; int maxpressure; int minpressure; int usage; } ;
typedef  int __u8 ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int DIGITIZER_USAGE_TILT_X ; 
 int DIGITIZER_USAGE_TILT_Y ; 
 int DIGITIZER_USAGE_TIP_PRESSURE ; 
 int PREF_SIZE (int) ; 
 int PREF_TAG (int) ; 
 int PREF_TYPE (int) ; 
#define  TAG_GLOB_LOG_MAX 147 
#define  TAG_GLOB_LOG_MIN 146 
 int TAG_GLOB_MAX ; 
#define  TAG_GLOB_PHYS_MAX 145 
#define  TAG_GLOB_PHYS_MIN 144 
#define  TAG_GLOB_POP 143 
#define  TAG_GLOB_PUSH 142 
#define  TAG_GLOB_REPORT_CNT 141 
#define  TAG_GLOB_REPORT_ID 140 
#define  TAG_GLOB_REPORT_SZ 139 
#define  TAG_GLOB_UNIT 138 
#define  TAG_GLOB_UNIT_EXP 137 
#define  TAG_GLOB_USAGE 136 
#define  TAG_MAIN_COL_END 135 
#define  TAG_MAIN_COL_START 134 
#define  TAG_MAIN_FEATURE 133 
#define  TAG_MAIN_INPUT 132 
#define  TAG_MAIN_OUTPUT 131 
#define  TYPE_GLOBAL 130 
#define  TYPE_LOCAL 129 
#define  TYPE_MAIN 128 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int get_unaligned_le16 (char*) ; 
 int get_unaligned_le32 (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void parse_hid_report_descriptor(struct gtco *device, char * report,
					int length)
{
	int   x, i = 0;

	/* Tag primitive vars */
	__u8   prefix;
	__u8   size;
	__u8   tag;
	__u8   type;
	__u8   data   = 0;
	__u16  data16 = 0;
	__u32  data32 = 0;

	/* For parsing logic */
	int   inputnum = 0;
	__u32 usage = 0;

	/* Global Values, indexed by TAG */
	__u32 globalval[TAG_GLOB_MAX];
	__u32 oldval[TAG_GLOB_MAX];

	/* Debug stuff */
	char  maintype = 'x';
	char  globtype[12];
	int   indent = 0;
	char  indentstr[10] = "";


	dbg("======>>>>>>PARSE<<<<<<======");

	/* Walk  this report and pull out the info we need */
	while (i < length) {
		prefix = report[i];

		/* Skip over prefix */
		i++;

		/* Determine data size and save the data in the proper variable */
		size = PREF_SIZE(prefix);
		switch (size) {
		case 1:
			data = report[i];
			break;
		case 2:
			data16 = get_unaligned_le16(&report[i]);
			break;
		case 3:
			size = 4;
			data32 = get_unaligned_le32(&report[i]);
			break;
		}

		/* Skip size of data */
		i += size;

		/* What we do depends on the tag type */
		tag  = PREF_TAG(prefix);
		type = PREF_TYPE(prefix);
		switch (type) {
		case TYPE_MAIN:
			strcpy(globtype, "");
			switch (tag) {

			case TAG_MAIN_INPUT:
				/*
				 * The INPUT MAIN tag signifies this is
				 * information from a report.  We need to
				 * figure out what it is and store the
				 * min/max values
				 */

				maintype = 'I';
				if (data == 2)
					strcpy(globtype, "Variable");
				else if (data == 3)
					strcpy(globtype, "Var|Const");

				dbg("::::: Saving Report: %d input #%d Max: 0x%X(%d) Min:0x%X(%d) of %d bits",
				    globalval[TAG_GLOB_REPORT_ID], inputnum,
				    globalval[TAG_GLOB_LOG_MAX], globalval[TAG_GLOB_LOG_MAX],
				    globalval[TAG_GLOB_LOG_MIN], globalval[TAG_GLOB_LOG_MIN],
				    globalval[TAG_GLOB_REPORT_SZ] * globalval[TAG_GLOB_REPORT_CNT]);


				/*
				  We can assume that the first two input items
				  are always the X and Y coordinates.  After
				  that, we look for everything else by
				  local usage value
				 */
				switch (inputnum) {
				case 0:  /* X coord */
					dbg("GER: X Usage: 0x%x", usage);
					if (device->max_X == 0) {
						device->max_X = globalval[TAG_GLOB_LOG_MAX];
						device->min_X = globalval[TAG_GLOB_LOG_MIN];
					}
					break;

				case 1:  /* Y coord */
					dbg("GER: Y Usage: 0x%x", usage);
					if (device->max_Y == 0) {
						device->max_Y = globalval[TAG_GLOB_LOG_MAX];
						device->min_Y = globalval[TAG_GLOB_LOG_MIN];
					}
					break;

				default:
					/* Tilt X */
					if (usage == DIGITIZER_USAGE_TILT_X) {
						if (device->maxtilt_X == 0) {
							device->maxtilt_X = globalval[TAG_GLOB_LOG_MAX];
							device->mintilt_X = globalval[TAG_GLOB_LOG_MIN];
						}
					}

					/* Tilt Y */
					if (usage == DIGITIZER_USAGE_TILT_Y) {
						if (device->maxtilt_Y == 0) {
							device->maxtilt_Y = globalval[TAG_GLOB_LOG_MAX];
							device->mintilt_Y = globalval[TAG_GLOB_LOG_MIN];
						}
					}

					/* Pressure */
					if (usage == DIGITIZER_USAGE_TIP_PRESSURE) {
						if (device->maxpressure == 0) {
							device->maxpressure = globalval[TAG_GLOB_LOG_MAX];
							device->minpressure = globalval[TAG_GLOB_LOG_MIN];
						}
					}

					break;
				}

				inputnum++;
				break;

			case TAG_MAIN_OUTPUT:
				maintype = 'O';
				break;

			case TAG_MAIN_FEATURE:
				maintype = 'F';
				break;

			case TAG_MAIN_COL_START:
				maintype = 'S';

				if (data == 0) {
					dbg("======>>>>>> Physical");
					strcpy(globtype, "Physical");
				} else
					dbg("======>>>>>>");

				/* Indent the debug output */
				indent++;
				for (x = 0; x < indent; x++)
					indentstr[x] = '-';
				indentstr[x] = 0;

				/* Save global tags */
				for (x = 0; x < TAG_GLOB_MAX; x++)
					oldval[x] = globalval[x];

				break;

			case TAG_MAIN_COL_END:
				dbg("<<<<<<======");
				maintype = 'E';
				indent--;
				for (x = 0; x < indent; x++)
					indentstr[x] = '-';
				indentstr[x] = 0;

				/* Copy global tags back */
				for (x = 0; x < TAG_GLOB_MAX; x++)
					globalval[x] = oldval[x];

				break;
			}

			switch (size) {
			case 1:
				dbg("%sMAINTAG:(%d) %c SIZE: %d Data: %s 0x%x",
				    indentstr, tag, maintype, size, globtype, data);
				break;

			case 2:
				dbg("%sMAINTAG:(%d) %c SIZE: %d Data: %s 0x%x",
				    indentstr, tag, maintype, size, globtype, data16);
				break;

			case 4:
				dbg("%sMAINTAG:(%d) %c SIZE: %d Data: %s 0x%x",
				    indentstr, tag, maintype, size, globtype, data32);
				break;
			}
			break;

		case TYPE_GLOBAL:
			switch (tag) {
			case TAG_GLOB_USAGE:
				/*
				 * First time we hit the global usage tag,
				 * it should tell us the type of device
				 */
				if (device->usage == 0)
					device->usage = data;

				strcpy(globtype, "USAGE");
				break;

			case TAG_GLOB_LOG_MIN:
				strcpy(globtype, "LOG_MIN");
				break;

			case TAG_GLOB_LOG_MAX:
				strcpy(globtype, "LOG_MAX");
				break;

			case TAG_GLOB_PHYS_MIN:
				strcpy(globtype, "PHYS_MIN");
				break;

			case TAG_GLOB_PHYS_MAX:
				strcpy(globtype, "PHYS_MAX");
				break;

			case TAG_GLOB_UNIT_EXP:
				strcpy(globtype, "EXP");
				break;

			case TAG_GLOB_UNIT:
				strcpy(globtype, "UNIT");
				break;

			case TAG_GLOB_REPORT_SZ:
				strcpy(globtype, "REPORT_SZ");
				break;

			case TAG_GLOB_REPORT_ID:
				strcpy(globtype, "REPORT_ID");
				/* New report, restart numbering */
				inputnum = 0;
				break;

			case TAG_GLOB_REPORT_CNT:
				strcpy(globtype, "REPORT_CNT");
				break;

			case TAG_GLOB_PUSH:
				strcpy(globtype, "PUSH");
				break;

			case TAG_GLOB_POP:
				strcpy(globtype, "POP");
				break;
			}

			/* Check to make sure we have a good tag number
			   so we don't overflow array */
			if (tag < TAG_GLOB_MAX) {
				switch (size) {
				case 1:
					dbg("%sGLOBALTAG:%s(%d) SIZE: %d Data: 0x%x",
					    indentstr, globtype, tag, size, data);
					globalval[tag] = data;
					break;

				case 2:
					dbg("%sGLOBALTAG:%s(%d) SIZE: %d Data: 0x%x",
					    indentstr, globtype, tag, size, data16);
					globalval[tag] = data16;
					break;

				case 4:
					dbg("%sGLOBALTAG:%s(%d) SIZE: %d Data: 0x%x",
					    indentstr, globtype, tag, size, data32);
					globalval[tag] = data32;
					break;
				}
			} else {
				dbg("%sGLOBALTAG: ILLEGAL TAG:%d SIZE: %d ",
				    indentstr, tag, size);
			}
			break;

		case TYPE_LOCAL:
			switch (tag) {
			case TAG_GLOB_USAGE:
				strcpy(globtype, "USAGE");
				/* Always 1 byte */
				usage = data;
				break;

			case TAG_GLOB_LOG_MIN:
				strcpy(globtype, "MIN");
				break;

			case TAG_GLOB_LOG_MAX:
				strcpy(globtype, "MAX");
				break;

			default:
				strcpy(globtype, "UNKNOWN");
				break;
			}

			switch (size) {
			case 1:
				dbg("%sLOCALTAG:(%d) %s SIZE: %d Data: 0x%x",
				    indentstr, tag, globtype, size, data);
				break;

			case 2:
				dbg("%sLOCALTAG:(%d) %s SIZE: %d Data: 0x%x",
				    indentstr, tag, globtype, size, data16);
				break;

			case 4:
				dbg("%sLOCALTAG:(%d) %s SIZE: %d Data: 0x%x",
				    indentstr, tag, globtype, size, data32);
				break;
			}

			break;
		}
	}
}