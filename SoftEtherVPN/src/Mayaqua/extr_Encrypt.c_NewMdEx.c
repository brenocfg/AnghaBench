#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hmac_ctx_st {int dummy; } ;
struct evp_md_st {int dummy; } ;
struct TYPE_4__ {int IsNullMd; int IsHMac; struct evp_md_st const* Md; void* Ctx; int /*<<< orphan*/  Size; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ MD ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int EVP_DigestInit_ex (void*,struct evp_md_st const*,int /*<<< orphan*/ *) ; 
 void* EVP_MD_CTX_create () ; 
 void* EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_get_digestbyname (char*) ; 
 int /*<<< orphan*/  FreeMd (TYPE_1__*) ; 
 int /*<<< orphan*/  HMAC_CTX_init (void*) ; 
 void* HMAC_CTX_new () ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  OpenSSL_Error () ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* ZeroMalloc (int) ; 

MD *NewMdEx(char *name, bool hmac)
{
	MD *m;

	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	m = ZeroMalloc(sizeof(MD));

	StrCpy(m->Name, sizeof(m->Name), name);

	if (StrCmpi(name, "[null-digest]") == 0 ||
		StrCmpi(name, "NULL") == 0 ||
		IsEmptyStr(name))
	{
		m->IsNullMd = true;
		return m;
	}

	m->Md = (const struct evp_md_st *)EVP_get_digestbyname(name);
	if (m->Md == NULL)
	{
		Debug("NewMdEx(): Algorithm %s not found by EVP_get_digestbyname().\n", m->Name);
		FreeMd(m);
		return NULL;
	}

	m->Size = EVP_MD_size((const EVP_MD *)m->Md);
	m->IsHMac = hmac;

	if (hmac)
	{
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
		m->Ctx = HMAC_CTX_new();
#else
		m->Ctx = ZeroMalloc(sizeof(struct hmac_ctx_st));
		HMAC_CTX_init(m->Ctx);
#endif
	}
	else
	{
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
		m->Ctx = EVP_MD_CTX_new();
#else
		m->Ctx = EVP_MD_CTX_create();
#endif
		if (EVP_DigestInit_ex(m->Ctx, m->Md, NULL) == false)
		{
			Debug("NewMdEx(): EVP_DigestInit_ex() failed with error: %s\n", OpenSSL_Error());
			FreeMd(m);
		}
	}

	return m;
}