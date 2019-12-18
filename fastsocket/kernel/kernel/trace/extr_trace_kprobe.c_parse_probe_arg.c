#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct trace_probe {int /*<<< orphan*/  size; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct probe_arg {char const* comm; TYPE_5__ fetch; TYPE_1__ fetch_size; TYPE_2__* type; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_ARGSTR_LEN ; 
 int __parse_bitfield_probe_arg (char const*,TYPE_2__*,TYPE_5__*) ; 
 int __parse_probe_arg (char*,TYPE_2__*,TYPE_5__*,int) ; 
 TYPE_2__* find_fetch_type (char const*) ; 
 int /*<<< orphan*/  get_fetch_size_function (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char const* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int parse_probe_arg(char *arg, struct trace_probe *tp,
			   struct probe_arg *parg, bool is_return)
{
	const char *t;
	int ret;

	if (strlen(arg) > MAX_ARGSTR_LEN) {
		pr_info("Argument is too long.: %s\n",  arg);
		return -ENOSPC;
	}
	parg->comm = kstrdup(arg, GFP_KERNEL);
	if (!parg->comm) {
		pr_info("Failed to allocate memory for command '%s'.\n", arg);
		return -ENOMEM;
	}
	t = strchr(parg->comm, ':');
	if (t) {
		arg[t - parg->comm] = '\0';
		t++;
	}
	parg->type = find_fetch_type(t);
	if (!parg->type) {
		pr_info("Unsupported type: %s\n", t);
		return -EINVAL;
	}
	parg->offset = tp->size;
	tp->size += parg->type->size;
	ret = __parse_probe_arg(arg, parg->type, &parg->fetch, is_return);
	if (ret >= 0 && t != NULL)
		ret = __parse_bitfield_probe_arg(t, parg->type, &parg->fetch);
	if (ret >= 0) {
		parg->fetch_size.fn = get_fetch_size_function(parg->type,
							      parg->fetch.fn);
		parg->fetch_size.data = parg->fetch.data;
	}
	return ret;
}