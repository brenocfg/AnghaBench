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
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct filter_arg {TYPE_1__ num; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
#define  FILTER_CMP_EQ 133 
#define  FILTER_CMP_GE 132 
#define  FILTER_CMP_GT 131 
#define  FILTER_CMP_LE 130 
#define  FILTER_CMP_LT 129 
#define  FILTER_CMP_NE 128 
 char* arg_to_str (struct event_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *num_to_str(struct event_filter *filter, struct filter_arg *arg)
{
	char *lstr;
	char *rstr;
	char *str = NULL;
	char *op = NULL;
	int len;

	lstr = arg_to_str(filter, arg->num.left);
	rstr = arg_to_str(filter, arg->num.right);
	if (!lstr || !rstr)
		goto out;

	switch (arg->num.type) {
	case FILTER_CMP_EQ:
		op = "==";
		/* fall through */
	case FILTER_CMP_NE:
		if (!op)
			op = "!=";
		/* fall through */
	case FILTER_CMP_GT:
		if (!op)
			op = ">";
		/* fall through */
	case FILTER_CMP_LT:
		if (!op)
			op = "<";
		/* fall through */
	case FILTER_CMP_GE:
		if (!op)
			op = ">=";
		/* fall through */
	case FILTER_CMP_LE:
		if (!op)
			op = "<=";

		len = strlen(lstr) + strlen(op) + strlen(rstr) + 4;
		str = malloc_or_die(len);
		sprintf(str, "%s %s %s", lstr, op, rstr);

		break;

	default:
		/* ?? */
		break;
	}

out:
	free(lstr);
	free(rstr);
	return str;
}