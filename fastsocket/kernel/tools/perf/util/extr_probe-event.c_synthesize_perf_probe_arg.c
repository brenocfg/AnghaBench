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
struct perf_probe_arg_field {char* name; struct perf_probe_arg_field* next; scalar_t__ ref; } ;
struct perf_probe_arg {char* name; char* var; char* type; struct perf_probe_arg_field* field; } ;

/* Variables and functions */
 int e_snprintf (char*,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

int synthesize_perf_probe_arg(struct perf_probe_arg *pa, char *buf, size_t len)
{
	struct perf_probe_arg_field *field = pa->field;
	int ret;
	char *tmp = buf;

	if (pa->name && pa->var)
		ret = e_snprintf(tmp, len, "%s=%s", pa->name, pa->var);
	else
		ret = e_snprintf(tmp, len, "%s", pa->name ? pa->name : pa->var);
	if (ret <= 0)
		goto error;
	tmp += ret;
	len -= ret;

	while (field) {
		if (field->name[0] == '[')
			ret = e_snprintf(tmp, len, "%s", field->name);
		else
			ret = e_snprintf(tmp, len, "%s%s",
					 field->ref ? "->" : ".", field->name);
		if (ret <= 0)
			goto error;
		tmp += ret;
		len -= ret;
		field = field->next;
	}

	if (pa->type) {
		ret = e_snprintf(tmp, len, ":%s", pa->type);
		if (ret <= 0)
			goto error;
		tmp += ret;
		len -= ret;
	}

	return tmp - buf;
error:
	pr_debug("Failed to synthesize perf probe argument: %s\n",
		 strerror(-ret));
	return ret;
}