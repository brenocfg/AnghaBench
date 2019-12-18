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
struct xfrm_user_tmpl {int dummy; } ;
struct xfrm_policy {int /*<<< orphan*/  family; scalar_t__ xfrm_nr; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t XFRMA_TMPL ; 
 int /*<<< orphan*/  copy_templates (struct xfrm_policy*,struct xfrm_user_tmpl*,int) ; 
 struct xfrm_user_tmpl* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int validate_tmpl (int,struct xfrm_user_tmpl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_from_user_tmpl(struct xfrm_policy *pol, struct nlattr **attrs)
{
	struct nlattr *rt = attrs[XFRMA_TMPL];

	if (!rt) {
		pol->xfrm_nr = 0;
	} else {
		struct xfrm_user_tmpl *utmpl = nla_data(rt);
		int nr = nla_len(rt) / sizeof(*utmpl);
		int err;

		err = validate_tmpl(nr, utmpl, pol->family);
		if (err)
			return err;

		copy_templates(pol, utmpl, nr);
	}
	return 0;
}