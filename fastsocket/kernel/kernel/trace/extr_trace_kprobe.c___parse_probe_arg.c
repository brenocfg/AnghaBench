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
struct fetch_type {int /*<<< orphan*/  name; int /*<<< orphan*/ * fetch; } ;
struct fetch_param {int /*<<< orphan*/  fn; void* data; } ;
struct deref_fetch_param {long offset; struct fetch_param orig; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t FETCH_MTD_deref ; 
 size_t FETCH_MTD_memory ; 
 size_t FETCH_MTD_reg ; 
 size_t FETCH_MTD_symbol ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* alloc_symbol_cache (char*,long) ; 
 struct fetch_type* find_fetch_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  kfree (struct deref_fetch_param*) ; 
 struct deref_fetch_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parse_probe_vars (char*,struct fetch_type const*,struct fetch_param*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int regs_query_register_offset (char*) ; 
 int split_symbol_offset (char*,long*) ; 
 char* strchr (char*,char) ; 
 int strict_strtol (char*,int /*<<< orphan*/ ,long*) ; 
 int strict_strtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int __parse_probe_arg(char *arg, const struct fetch_type *t,
			     struct fetch_param *f, bool is_return)
{
	int ret = 0;
	unsigned long param;
	long offset;
	char *tmp;

	switch (arg[0]) {
	case '$':
		ret = parse_probe_vars(arg + 1, t, f, is_return);
		break;
	case '%':	/* named register */
		ret = regs_query_register_offset(arg + 1);
		if (ret >= 0) {
			f->fn = t->fetch[FETCH_MTD_reg];
			f->data = (void *)(unsigned long)ret;
			ret = 0;
		}
		break;
	case '@':	/* memory or symbol */
		if (isdigit(arg[1])) {
			ret = strict_strtoul(arg + 1, 0, &param);
			if (ret)
				break;
			f->fn = t->fetch[FETCH_MTD_memory];
			f->data = (void *)param;
		} else {
			ret = split_symbol_offset(arg + 1, &offset);
			if (ret)
				break;
			f->data = alloc_symbol_cache(arg + 1, offset);
			if (f->data)
				f->fn = t->fetch[FETCH_MTD_symbol];
		}
		break;
	case '+':	/* deref memory */
		arg++;	/* Skip '+', because strict_strtol() rejects it. */
	case '-':
		tmp = strchr(arg, '(');
		if (!tmp)
			break;
		*tmp = '\0';
		ret = strict_strtol(arg, 0, &offset);
		if (ret)
			break;
		arg = tmp + 1;
		tmp = strrchr(arg, ')');
		if (tmp) {
			struct deref_fetch_param *dprm;
			const struct fetch_type *t2 = find_fetch_type(NULL);
			*tmp = '\0';
			dprm = kzalloc(sizeof(struct deref_fetch_param),
				       GFP_KERNEL);
			if (!dprm)
				return -ENOMEM;
			dprm->offset = offset;
			ret = __parse_probe_arg(arg, t2, &dprm->orig,
						is_return);
			if (ret)
				kfree(dprm);
			else {
				f->fn = t->fetch[FETCH_MTD_deref];
				f->data = (void *)dprm;
			}
		}
		break;
	}
	if (!ret && !f->fn) {	/* Parsed, but do not find fetch method */
		pr_info("%s type has no corresponding fetch method.\n",
			t->name);
		ret = -EINVAL;
	}
	return ret;
}