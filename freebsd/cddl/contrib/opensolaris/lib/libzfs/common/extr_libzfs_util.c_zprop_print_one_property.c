#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int zprop_source_t ;
struct TYPE_4__ {int cb_sources; int* cb_columns; char** cb_colwidths; scalar_t__ cb_scripted; int /*<<< orphan*/  cb_type; scalar_t__ cb_first; } ;
typedef  TYPE_1__ zprop_get_cbdata_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  GET_COL_NAME 138 
 int GET_COL_NONE ; 
#define  GET_COL_PROPERTY 137 
#define  GET_COL_RECVD 136 
#define  GET_COL_SOURCE 135 
#define  GET_COL_VALUE 134 
 int ZFS_GET_NCOLS ; 
#define  ZPROP_SRC_DEFAULT 133 
#define  ZPROP_SRC_INHERITED 132 
#define  ZPROP_SRC_LOCAL 131 
#define  ZPROP_SRC_NONE 130 
#define  ZPROP_SRC_RECEIVED 129 
#define  ZPROP_SRC_TEMPORARY 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  zprop_print_headers (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
zprop_print_one_property(const char *name, zprop_get_cbdata_t *cbp,
    const char *propname, const char *value, zprop_source_t sourcetype,
    const char *source, const char *recvd_value)
{
	int i;
	const char *str = NULL;
	char buf[128];

	/*
	 * Ignore those source types that the user has chosen to ignore.
	 */
	if ((sourcetype & cbp->cb_sources) == 0)
		return;

	if (cbp->cb_first)
		zprop_print_headers(cbp, cbp->cb_type);

	for (i = 0; i < ZFS_GET_NCOLS; i++) {
		switch (cbp->cb_columns[i]) {
		case GET_COL_NAME:
			str = name;
			break;

		case GET_COL_PROPERTY:
			str = propname;
			break;

		case GET_COL_VALUE:
			str = value;
			break;

		case GET_COL_SOURCE:
			switch (sourcetype) {
			case ZPROP_SRC_NONE:
				str = "-";
				break;

			case ZPROP_SRC_DEFAULT:
				str = "default";
				break;

			case ZPROP_SRC_LOCAL:
				str = "local";
				break;

			case ZPROP_SRC_TEMPORARY:
				str = "temporary";
				break;

			case ZPROP_SRC_INHERITED:
				(void) snprintf(buf, sizeof (buf),
				    "inherited from %s", source);
				str = buf;
				break;
			case ZPROP_SRC_RECEIVED:
				str = "received";
				break;

			default:
				str = NULL;
				assert(!"unhandled zprop_source_t");
			}
			break;

		case GET_COL_RECVD:
			str = (recvd_value == NULL ? "-" : recvd_value);
			break;

		default:
			continue;
		}

		if (cbp->cb_columns[i + 1] == GET_COL_NONE)
			(void) printf("%s", str);
		else if (cbp->cb_scripted)
			(void) printf("%s\t", str);
		else
			(void) printf("%-*s  ",
			    cbp->cb_colwidths[cbp->cb_columns[i]],
			    str);
	}

	(void) printf("\n");
}