#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cn_username ;
struct TYPE_6__ {TYPE_1__* subject_name; } ;
typedef  TYPE_2__ X ;
struct TYPE_5__ {int /*<<< orphan*/  CommonName; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHTYPE_OPENVPN_CERT ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (TYPE_2__*,int) ; 

PACK *PackLoginWithOpenVPNCertificate(char *hubname, char *username, X *x)
{
	PACK *p;
	char cn_username[128];
	BUF *cert_buf = NULL;
	// Validate arguments
	if (hubname == NULL || username == NULL || x == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "method", "login");
	PackAddStr(p, "hubname", hubname);

	if (IsEmptyStr(username))
	{
		if (x->subject_name == NULL)
		{
			FreePack(p);
			return NULL;
		}
		UniToStr(cn_username, sizeof(cn_username), x->subject_name->CommonName);
		PackAddStr(p, "username", cn_username);
	}
	else
	{
		PackAddStr(p, "username", username);
	}

	PackAddInt(p, "authtype", AUTHTYPE_OPENVPN_CERT);

	cert_buf = XToBuf(x, false);
	PackAddBuf(p, "cert", cert_buf);
	FreeBuf(cert_buf);

	return p;
}