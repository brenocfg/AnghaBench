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
typedef  int /*<<< orphan*/  password_hash_2 ;
typedef  int /*<<< orphan*/  key3 ;
typedef  int /*<<< orphan*/  key2 ;
typedef  int /*<<< orphan*/  key1 ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DesEcbEncrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void MsChapV2Client_GenerateResponse(UCHAR *dst, UCHAR *challenge8, UCHAR *nt_password_hash)
{
	UCHAR password_hash_2[21];
	UCHAR key1[8], key2[8], key3[8];
	// Validate arguments
	if (dst == NULL || challenge8 == NULL || nt_password_hash == NULL)
	{
		return;
	}

	Zero(password_hash_2, sizeof(password_hash_2));
	Copy(password_hash_2, nt_password_hash, 16);

	Zero(key1, sizeof(key1));
	Zero(key2, sizeof(key2));
	Zero(key3, sizeof(key3));

	Copy(key1, password_hash_2 + 0, 7);
	Copy(key2, password_hash_2 + 7, 7);
	Copy(key3, password_hash_2 + 14, 7);

	DesEcbEncrypt(dst + 0, challenge8, key1);
	DesEcbEncrypt(dst + 8, challenge8, key2);
	DesEcbEncrypt(dst + 16, challenge8, key3);
}