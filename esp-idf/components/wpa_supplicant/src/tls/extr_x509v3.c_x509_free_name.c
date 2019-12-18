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
struct x509_name {size_t num_attr; int /*<<< orphan*/  rid; scalar_t__ ip_len; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * uri; int /*<<< orphan*/ * dns; int /*<<< orphan*/ * alt_email; int /*<<< orphan*/ * email; TYPE_1__* attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  X509_NAME_ATTR_NOT_USED ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void x509_free_name(struct x509_name *name)
{
	size_t i;

	for (i = 0; i < name->num_attr; i++) {
		os_free(name->attr[i].value);
		name->attr[i].value = NULL;
		name->attr[i].type = X509_NAME_ATTR_NOT_USED;
	}
	name->num_attr = 0;
	os_free(name->email);
	name->email = NULL;

	os_free(name->alt_email);
	os_free(name->dns);
	os_free(name->uri);
	os_free(name->ip);
	name->alt_email = name->dns = name->uri = NULL;
	name->ip = NULL;
	name->ip_len = 0;
	os_memset(&name->rid, 0, sizeof(name->rid));
}