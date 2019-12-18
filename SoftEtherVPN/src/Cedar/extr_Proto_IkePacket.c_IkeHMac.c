#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int HashId; } ;
typedef  int /*<<< orphan*/  MD ;
typedef  TYPE_1__ IKE_HASH ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  FreeMd (int /*<<< orphan*/ *) ; 
#define  IKE_HASH_MD5_ID 132 
#define  IKE_HASH_SHA1_ID 131 
#define  IKE_HASH_SHA2_256_ID 130 
#define  IKE_HASH_SHA2_384_ID 129 
#define  IKE_HASH_SHA2_512_ID 128 
 scalar_t__ MdProcess (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewMd (char*) ; 
 int SetMdKey (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

void IkeHMac(IKE_HASH *h, void *dst, void *key, UINT key_size, void *data, UINT data_size)
{
	MD *md = NULL;

	switch (h->HashId)
	{
	case IKE_HASH_MD5_ID:
		md = NewMd("MD5");
		break;
	case IKE_HASH_SHA1_ID:
		md = NewMd("SHA1");
		break;
	case IKE_HASH_SHA2_256_ID:
		md = NewMd("SHA256");
		break;
	case IKE_HASH_SHA2_384_ID:
		md = NewMd("SHA384");
		break;
	case IKE_HASH_SHA2_512_ID:
		md = NewMd("SHA512");
		break;
	}

	if (md == NULL)
	{
		Debug("IkeHMac(): The MD object is NULL! Either NewMd() failed or the current algorithm is not handled by the switch-case block.\n");
		return;
	}

	if (SetMdKey(md, key, key_size) == false)
	{
		Debug("IkeHMac(): SetMdKey() failed!\n");
		goto cleanup;
	}

	if (MdProcess(md, dst, data, data_size) == 0)
	{
		Debug("IkeHMac(): MdProcess() returned 0!\n");
	}

cleanup:
	FreeMd(md);
}