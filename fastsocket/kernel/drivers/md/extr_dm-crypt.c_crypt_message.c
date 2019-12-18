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
struct dm_target {struct crypt_config* private; } ;
struct crypt_config {TYPE_1__* iv_gen_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int (* init ) (struct crypt_config*) ;int (* wipe ) (struct crypt_config*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  DM_CRYPT_SUSPENDED ; 
 int EINVAL ; 
 int crypt_set_key (struct crypt_config*,char*) ; 
 int crypt_wipe_key (struct crypt_config*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int stub1 (struct crypt_config*) ; 
 int stub2 (struct crypt_config*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypt_message(struct dm_target *ti, unsigned argc, char **argv)
{
	struct crypt_config *cc = ti->private;
	int ret = -EINVAL;

	if (argc < 2)
		goto error;

	if (!strcasecmp(argv[0], "key")) {
		if (!test_bit(DM_CRYPT_SUSPENDED, &cc->flags)) {
			DMWARN("not suspended during key manipulation.");
			return -EINVAL;
		}
		if (argc == 3 && !strcasecmp(argv[1], "set")) {
			ret = crypt_set_key(cc, argv[2]);
			if (ret)
				return ret;
			if (cc->iv_gen_ops && cc->iv_gen_ops->init)
				ret = cc->iv_gen_ops->init(cc);
			return ret;
		}
		if (argc == 2 && !strcasecmp(argv[1], "wipe")) {
			if (cc->iv_gen_ops && cc->iv_gen_ops->wipe) {
				ret = cc->iv_gen_ops->wipe(cc);
				if (ret)
					return ret;
			}
			return crypt_wipe_key(cc);
		}
	}

error:
	DMWARN("unrecognised message received.");
	return -EINVAL;
}