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
typedef  int /*<<< orphan*/  substring_t ;
struct pohmelfs_sb {int idx; int trans_retries; int crypto_thread_num; int trans_max_pages; int crypto_fail_unsupported; void* mcache_timeout; void* wait_on_page_timeout; void* drop_scan_timeout; void* trans_scan_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* msecs_to_jiffies (int) ; 
#define  pohmelfs_opt_crypto_fail_unsupported 136 
#define  pohmelfs_opt_crypto_thread_num 135 
#define  pohmelfs_opt_drop_scan_timeout 134 
#define  pohmelfs_opt_idx 133 
#define  pohmelfs_opt_mcache_timeout 132 
#define  pohmelfs_opt_trans_max_pages 131 
#define  pohmelfs_opt_trans_retries 130 
#define  pohmelfs_opt_trans_scan_timeout 129 
#define  pohmelfs_opt_wait_on_page_timeout 128 
 int /*<<< orphan*/  pohmelfs_tokens ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int pohmelfs_parse_options(char *options, struct pohmelfs_sb *psb, int remount)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option, err;

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, pohmelfs_tokens, args);

		err = match_int(&args[0], &option);
		if (err)
			return err;

		if (remount && token <= pohmelfs_opt_crypto_fail_unsupported)
			continue;

		switch (token) {
			case pohmelfs_opt_idx:
				psb->idx = option;
				break;
			case pohmelfs_opt_trans_scan_timeout:
				psb->trans_scan_timeout = msecs_to_jiffies(option);
				break;
			case pohmelfs_opt_drop_scan_timeout:
				psb->drop_scan_timeout = msecs_to_jiffies(option);
				break;
			case pohmelfs_opt_wait_on_page_timeout:
				psb->wait_on_page_timeout = msecs_to_jiffies(option);
				break;
			case pohmelfs_opt_mcache_timeout:
				psb->mcache_timeout = msecs_to_jiffies(option);
				break;
			case pohmelfs_opt_trans_retries:
				psb->trans_retries = option;
				break;
			case pohmelfs_opt_crypto_thread_num:
				psb->crypto_thread_num = option;
				break;
			case pohmelfs_opt_trans_max_pages:
				psb->trans_max_pages = option;
				break;
			case pohmelfs_opt_crypto_fail_unsupported:
				psb->crypto_fail_unsupported = 1;
				break;
			default:
				return -EINVAL;
		}
	}

	return 0;
}