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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; int /*<<< orphan*/  Name; TYPE_3__* Serial; } ;
typedef  TYPE_1__ CRL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 TYPE_3__* NewXSerial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 TYPE_1__* ZeroMalloc (int) ; 

CRL *CopyCrl(CRL *crl)
{
	CRL *ret;
	// Validate arguments
	if (crl == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(CRL));

	if (crl->Serial != NULL)
	{
		ret->Serial = NewXSerial(crl->Serial->data, crl->Serial->size);
	}

	ret->Name = CopyName(crl->Name);

	Copy(ret->DigestMD5, crl->DigestMD5, MD5_SIZE);
	Copy(ret->DigestSHA1, crl->DigestSHA1, SHA1_SIZE);

	return ret;
}