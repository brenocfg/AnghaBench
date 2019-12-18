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
struct filter_arg {TYPE_1__ exp; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
#define  FILTER_EXP_ADD 137 
#define  FILTER_EXP_AND 136 
#define  FILTER_EXP_DIV 135 
#define  FILTER_EXP_LSHIFT 134 
#define  FILTER_EXP_MOD 133 
#define  FILTER_EXP_MUL 132 
#define  FILTER_EXP_OR 131 
#define  FILTER_EXP_RSHIFT 130 
#define  FILTER_EXP_SUB 129 
#define  FILTER_EXP_XOR 128 
 char* arg_to_str (struct event_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *exp_to_str(struct event_filter *filter, struct filter_arg *arg)
{
	char *lstr;
	char *rstr;
	char *op;
	char *str = NULL;
	int len;

	lstr = arg_to_str(filter, arg->exp.left);
	rstr = arg_to_str(filter, arg->exp.right);
	if (!lstr || !rstr)
		goto out;

	switch (arg->exp.type) {
	case FILTER_EXP_ADD:
		op = "+";
		break;
	case FILTER_EXP_SUB:
		op = "-";
		break;
	case FILTER_EXP_MUL:
		op = "*";
		break;
	case FILTER_EXP_DIV:
		op = "/";
		break;
	case FILTER_EXP_MOD:
		op = "%";
		break;
	case FILTER_EXP_RSHIFT:
		op = ">>";
		break;
	case FILTER_EXP_LSHIFT:
		op = "<<";
		break;
	case FILTER_EXP_AND:
		op = "&";
		break;
	case FILTER_EXP_OR:
		op = "|";
		break;
	case FILTER_EXP_XOR:
		op = "^";
		break;
	default:
		die("oops in exp");
	}

	len = strlen(op) + strlen(lstr) + strlen(rstr) + 4;
	str = malloc_or_die(len);
	snprintf(str, len, "%s %s %s", lstr, op, rstr);
out:
	free(lstr);
	free(rstr);

	return str;
}