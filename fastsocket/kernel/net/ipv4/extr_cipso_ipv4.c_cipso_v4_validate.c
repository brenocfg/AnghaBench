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
typedef  int u8 ;
typedef  size_t u32 ;
struct sk_buff {TYPE_1__* dev; } ;
struct cipso_v4_doi {unsigned char* tags; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned char CIPSO_V4_HDR_LEN ; 
#define  CIPSO_V4_TAG_ENUM 131 
 int CIPSO_V4_TAG_ENUM_BLEN ; 
 unsigned char CIPSO_V4_TAG_INVALID ; 
#define  CIPSO_V4_TAG_LOCAL 130 
 int CIPSO_V4_TAG_LOC_BLEN ; 
 size_t CIPSO_V4_TAG_MAXCNT ; 
#define  CIPSO_V4_TAG_RANGE 129 
#define  CIPSO_V4_TAG_RBITMAP 128 
 int CIPSO_V4_TAG_RBM_BLEN ; 
 int CIPSO_V4_TAG_RNG_BLEN ; 
 int IFF_LOOPBACK ; 
 struct cipso_v4_doi* cipso_v4_doi_search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipso_v4_map_cat_enum_valid (struct cipso_v4_doi*,unsigned char*,int) ; 
 int /*<<< orphan*/  cipso_v4_map_cat_rbm_valid (struct cipso_v4_doi*,unsigned char*,int) ; 
 int /*<<< orphan*/  cipso_v4_map_cat_rng_valid (struct cipso_v4_doi*,unsigned char*,int) ; 
 int /*<<< orphan*/  cipso_v4_map_lvl_valid (struct cipso_v4_doi*,unsigned char) ; 
 int /*<<< orphan*/  cipso_v4_rbm_strictvalid ; 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int cipso_v4_validate(const struct sk_buff *skb, unsigned char **option)
{
	unsigned char *opt = *option;
	unsigned char *tag;
	unsigned char opt_iter;
	unsigned char err_offset = 0;
	u8 opt_len;
	u8 tag_len;
	struct cipso_v4_doi *doi_def = NULL;
	u32 tag_iter;

	/* caller already checks for length values that are too large */
	opt_len = opt[1];
	if (opt_len < 8) {
		err_offset = 1;
		goto validate_return;
	}

	rcu_read_lock();
	doi_def = cipso_v4_doi_search(get_unaligned_be32(&opt[2]));
	if (doi_def == NULL) {
		err_offset = 2;
		goto validate_return_locked;
	}

	opt_iter = CIPSO_V4_HDR_LEN;
	tag = opt + opt_iter;
	while (opt_iter < opt_len) {
		for (tag_iter = 0; doi_def->tags[tag_iter] != tag[0];)
			if (doi_def->tags[tag_iter] == CIPSO_V4_TAG_INVALID ||
			    ++tag_iter == CIPSO_V4_TAG_MAXCNT) {
				err_offset = opt_iter;
				goto validate_return_locked;
			}

		tag_len = tag[1];
		if (tag_len > (opt_len - opt_iter)) {
			err_offset = opt_iter + 1;
			goto validate_return_locked;
		}

		switch (tag[0]) {
		case CIPSO_V4_TAG_RBITMAP:
			if (tag_len < CIPSO_V4_TAG_RBM_BLEN) {
				err_offset = opt_iter + 1;
				goto validate_return_locked;
			}

			/* We are already going to do all the verification
			 * necessary at the socket layer so from our point of
			 * view it is safe to turn these checks off (and less
			 * work), however, the CIPSO draft says we should do
			 * all the CIPSO validations here but it doesn't
			 * really specify _exactly_ what we need to validate
			 * ... so, just make it a sysctl tunable. */
			if (cipso_v4_rbm_strictvalid) {
				if (cipso_v4_map_lvl_valid(doi_def,
							   tag[3]) < 0) {
					err_offset = opt_iter + 3;
					goto validate_return_locked;
				}
				if (tag_len > CIPSO_V4_TAG_RBM_BLEN &&
				    cipso_v4_map_cat_rbm_valid(doi_def,
							    &tag[4],
							    tag_len - 4) < 0) {
					err_offset = opt_iter + 4;
					goto validate_return_locked;
				}
			}
			break;
		case CIPSO_V4_TAG_ENUM:
			if (tag_len < CIPSO_V4_TAG_ENUM_BLEN) {
				err_offset = opt_iter + 1;
				goto validate_return_locked;
			}

			if (cipso_v4_map_lvl_valid(doi_def,
						   tag[3]) < 0) {
				err_offset = opt_iter + 3;
				goto validate_return_locked;
			}
			if (tag_len > CIPSO_V4_TAG_ENUM_BLEN &&
			    cipso_v4_map_cat_enum_valid(doi_def,
							&tag[4],
							tag_len - 4) < 0) {
				err_offset = opt_iter + 4;
				goto validate_return_locked;
			}
			break;
		case CIPSO_V4_TAG_RANGE:
			if (tag_len < CIPSO_V4_TAG_RNG_BLEN) {
				err_offset = opt_iter + 1;
				goto validate_return_locked;
			}

			if (cipso_v4_map_lvl_valid(doi_def,
						   tag[3]) < 0) {
				err_offset = opt_iter + 3;
				goto validate_return_locked;
			}
			if (tag_len > CIPSO_V4_TAG_RNG_BLEN &&
			    cipso_v4_map_cat_rng_valid(doi_def,
						       &tag[4],
						       tag_len - 4) < 0) {
				err_offset = opt_iter + 4;
				goto validate_return_locked;
			}
			break;
		case CIPSO_V4_TAG_LOCAL:
			/* This is a non-standard tag that we only allow for
			 * local connections, so if the incoming interface is
			 * not the loopback device drop the packet. Further,
			 * there is no legitimate reason for setting this from
			 * userspace so reject it if skb is NULL. */
			if (skb == NULL || !(skb->dev->flags & IFF_LOOPBACK)) {
				err_offset = opt_iter;
				goto validate_return_locked;
			}
			if (tag_len != CIPSO_V4_TAG_LOC_BLEN) {
				err_offset = opt_iter + 1;
				goto validate_return_locked;
			}
			break;
		default:
			err_offset = opt_iter;
			goto validate_return_locked;
		}

		tag += tag_len;
		opt_iter += tag_len;
	}

validate_return_locked:
	rcu_read_unlock();
validate_return:
	*option = opt + err_offset;
	return err_offset;
}