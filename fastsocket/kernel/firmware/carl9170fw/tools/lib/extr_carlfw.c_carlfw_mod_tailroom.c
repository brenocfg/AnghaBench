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
struct TYPE_2__ {size_t len; void* data; } ;
struct carlfw {TYPE_1__ fw; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170fw_size_check (size_t) ; 
 void* realloc (void*,size_t) ; 

void *carlfw_mod_tailroom(struct carlfw *fw, ssize_t len)
{
	size_t new_len;
	void *buf;

	new_len = fw->fw.len + len;

	if (!carl9170fw_size_check(new_len))
		return ERR_PTR(-EINVAL);

	buf = realloc(fw->fw.data, new_len);
	if (buf == NULL)
		return ERR_PTR(-ENOMEM);

	fw->fw.len = new_len;
	fw->fw.data = buf;
	return &fw->fw.data[new_len - len];
}