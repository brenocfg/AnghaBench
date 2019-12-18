#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nls_table {int dummy; } ;
struct dfs_referral_level_3 {scalar_t__ VersionNumber; scalar_t__ ServerType; scalar_t__ ReferralEntryFlags; scalar_t__ DfsPathOffset; scalar_t__ NetworkAddressOffset; } ;
struct dfs_info3_param {int path_consumed; int server_type; int ref_flag; void* node_name; void* path_name; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {scalar_t__ DataCount; } ;
struct TYPE_5__ {int Flags2; } ;
struct TYPE_7__ {scalar_t__ NumberOfReferrals; scalar_t__ PathConsumed; int /*<<< orphan*/  DFSFlags; TYPE_2__ t2; int /*<<< orphan*/  referrals; TYPE_1__ hdr; } ;
typedef  TYPE_3__ TRANSACTION2_GET_DFS_REFER_RSP ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  cERROR (int,char*,...) ; 
 int /*<<< orphan*/  cFYI (int,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifsConvertToUCS (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct nls_table const*,int) ; 
 void* cifs_strndup_from_ucs (char*,int,int,struct nls_table const*) ; 
 int cifs_ucs2_bytes (int /*<<< orphan*/ *,int,struct nls_table const*) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  free_dfs_info_array (struct dfs_info3_param*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dfs_info3_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
parse_DFS_referrals(TRANSACTION2_GET_DFS_REFER_RSP *pSMBr,
		unsigned int *num_of_nodes,
		struct dfs_info3_param **target_nodes,
		const struct nls_table *nls_codepage, int remap,
		const char *searchName)
{
	int i, rc = 0;
	char *data_end;
	bool is_unicode;
	struct dfs_referral_level_3 *ref;

	if (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
		is_unicode = true;
	else
		is_unicode = false;
	*num_of_nodes = le16_to_cpu(pSMBr->NumberOfReferrals);

	if (*num_of_nodes < 1) {
		cERROR(1, "num_referrals: must be at least > 0,"
			"but we get num_referrals = %d\n", *num_of_nodes);
		rc = -EINVAL;
		goto parse_DFS_referrals_exit;
	}

	ref = (struct dfs_referral_level_3 *) &(pSMBr->referrals);
	if (ref->VersionNumber != cpu_to_le16(3)) {
		cERROR(1, "Referrals of V%d version are not supported,"
			"should be V3", le16_to_cpu(ref->VersionNumber));
		rc = -EINVAL;
		goto parse_DFS_referrals_exit;
	}

	/* get the upper boundary of the resp buffer */
	data_end = (char *)(&(pSMBr->PathConsumed)) +
				le16_to_cpu(pSMBr->t2.DataCount);

	cFYI(1, "num_referrals: %d dfs flags: 0x%x ...\n",
			*num_of_nodes,
			le32_to_cpu(pSMBr->DFSFlags));

	*target_nodes = kzalloc(sizeof(struct dfs_info3_param) *
			*num_of_nodes, GFP_KERNEL);
	if (*target_nodes == NULL) {
		cERROR(1, "Failed to allocate buffer for target_nodes\n");
		rc = -ENOMEM;
		goto parse_DFS_referrals_exit;
	}

	/* collect neccessary data from referrals */
	for (i = 0; i < *num_of_nodes; i++) {
		char *temp;
		int max_len;
		struct dfs_info3_param *node = (*target_nodes)+i;

		node->flags = le32_to_cpu(pSMBr->DFSFlags);
		if (is_unicode) {
			__le16 *tmp = kmalloc(strlen(searchName)*2 + 2,
						GFP_KERNEL);
			if (tmp == NULL) {
				rc = -ENOMEM;
				goto parse_DFS_referrals_exit;
			}
			cifsConvertToUCS((__le16 *) tmp, searchName,
					PATH_MAX, nls_codepage, remap);
			node->path_consumed = cifs_ucs2_bytes(tmp,
					le16_to_cpu(pSMBr->PathConsumed),
					nls_codepage);
			kfree(tmp);
		} else
			node->path_consumed = le16_to_cpu(pSMBr->PathConsumed);

		node->server_type = le16_to_cpu(ref->ServerType);
		node->ref_flag = le16_to_cpu(ref->ReferralEntryFlags);

		/* copy DfsPath */
		temp = (char *)ref + le16_to_cpu(ref->DfsPathOffset);
		max_len = data_end - temp;
		node->path_name = cifs_strndup_from_ucs(temp, max_len,
						      is_unicode, nls_codepage);
		if (!node->path_name) {
			rc = -ENOMEM;
			goto parse_DFS_referrals_exit;
		}

		/* copy link target UNC */
		temp = (char *)ref + le16_to_cpu(ref->NetworkAddressOffset);
		max_len = data_end - temp;
		node->node_name = cifs_strndup_from_ucs(temp, max_len,
						      is_unicode, nls_codepage);
		if (!node->node_name)
			rc = -ENOMEM;
	}

parse_DFS_referrals_exit:
	if (rc) {
		free_dfs_info_array(*target_nodes, *num_of_nodes);
		*target_nodes = NULL;
		*num_of_nodes = 0;
	}
	return rc;
}