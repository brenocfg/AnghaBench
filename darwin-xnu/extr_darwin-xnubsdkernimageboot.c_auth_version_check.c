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
typedef  int /*<<< orphan*/  const uuid_t ;
typedef  unsigned long uuid_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHPRNT (char*,...) ; 
 int EINVAL ; 
 int OSKextGetUUIDForName (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ bcmp (int /*<<< orphan*/  const,int /*<<< orphan*/  const*,unsigned long) ; 
 int /*<<< orphan*/  const* getuuidfromheader_safe (void*,size_t,unsigned long*) ; 
 int /*<<< orphan*/  kfree_safe (void*) ; 
 int /*<<< orphan*/  libkern_bundle ; 
 unsigned long libkern_path ; 
 int read_file (unsigned long,void**,size_t*) ; 
 int /*<<< orphan*/  uuid_unparse (int /*<<< orphan*/  const,unsigned long) ; 

__attribute__((used)) static int
auth_version_check(void)
{
	int err = 0;
	void *buf = NULL;
	size_t bufsz = 4*1024*1024UL;

	/* get the UUID of the libkern in /S/L/E */

	err = read_file(libkern_path, &buf, &bufsz);
	if (err) {
		goto out;
	}

	unsigned long uuidsz = 0;
	const uuid_t *img_uuid = getuuidfromheader_safe(buf, bufsz, &uuidsz);
	if (img_uuid == NULL || uuidsz != sizeof(uuid_t)) {
		AUTHPRNT("invalid UUID (sz = %lu)", uuidsz);
		err = EINVAL;
		goto out;
	}

	/* Get the UUID of the loaded libkern */
	uuid_t live_uuid;
	err = OSKextGetUUIDForName(libkern_bundle, live_uuid);
	if (err) {
		AUTHPRNT("could not find loaded libkern");
		goto out;
	}

	/* ... and compare them */
	if (bcmp(live_uuid, img_uuid, uuidsz) != 0) {
		AUTHPRNT("UUID of running libkern does not match %s", libkern_path);

		uuid_string_t img_uuid_str, live_uuid_str;
		uuid_unparse(*img_uuid, img_uuid_str);
		uuid_unparse(live_uuid, live_uuid_str);
		AUTHPRNT("loaded libkern UUID =  %s", live_uuid_str);
		AUTHPRNT("on-disk libkern UUID = %s", img_uuid_str);

		err = EINVAL;
		goto out;
	}

	/* UUID matches! */

out:
	kfree_safe(buf);
	return err;
}