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
typedef  int /*<<< orphan*/  u32 ;
struct qstr {char* len; int /*<<< orphan*/  name; } ;
struct dlm_protocol_version {int dummy; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dlm_ctxt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct dlm_ctxt* dlm_register_domain (char*,int /*<<< orphan*/ ,struct dlm_protocol_version*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 

struct dlm_ctxt *user_dlm_register_context(struct qstr *name,
					   struct dlm_protocol_version *proto)
{
	struct dlm_ctxt *dlm;
	u32 dlm_key;
	char *domain;

	domain = kmalloc(name->len + 1, GFP_NOFS);
	if (!domain) {
		mlog_errno(-ENOMEM);
		return ERR_PTR(-ENOMEM);
	}

	dlm_key = crc32_le(0, name->name, name->len);

	snprintf(domain, name->len + 1, "%.*s", name->len, name->name);

	dlm = dlm_register_domain(domain, dlm_key, proto);
	if (IS_ERR(dlm))
		mlog_errno(PTR_ERR(dlm));

	kfree(domain);
	return dlm;
}