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
struct smb_vol {int secFlg; } ;
struct TCP_Server_Info {int secType; int sec_mode; } ;

/* Variables and functions */
 unsigned int CIFSSEC_MAY_KRB5 ; 
 unsigned int CIFSSEC_MAY_LANMAN ; 
 unsigned int CIFSSEC_MAY_NTLM ; 
 unsigned int CIFSSEC_MAY_NTLMSSP ; 
 unsigned int CIFSSEC_MAY_NTLMV2 ; 
 unsigned int CIFSSEC_MAY_PLNTXT ; 
 unsigned int CIFSSEC_MAY_SIGN ; 
 int CIFSSEC_MUST_SEAL ; 
 int CIFSSEC_MUST_SIGN ; 
#define  Kerberos 132 
#define  LANMAN 131 
#define  NTLM 130 
#define  NTLMv2 129 
#define  RawNTLMSSP 128 
 int SECMODE_SIGN_ENABLED ; 
 int SECMODE_SIGN_REQUIRED ; 
 unsigned int global_secflags ; 

__attribute__((used)) static bool
match_security(struct TCP_Server_Info *server, struct smb_vol *vol)
{
	unsigned int secFlags;

	if (vol->secFlg & (~(CIFSSEC_MUST_SIGN | CIFSSEC_MUST_SEAL)))
		secFlags = vol->secFlg;
	else
		secFlags = global_secflags | vol->secFlg;

	switch (server->secType) {
	case LANMAN:
		if (!(secFlags & (CIFSSEC_MAY_LANMAN|CIFSSEC_MAY_PLNTXT)))
			return false;
		break;
	case NTLMv2:
		if (!(secFlags & CIFSSEC_MAY_NTLMV2))
			return false;
		break;
	case NTLM:
		if (!(secFlags & CIFSSEC_MAY_NTLM))
			return false;
		break;
	case Kerberos:
		if (!(secFlags & CIFSSEC_MAY_KRB5))
			return false;
		break;
	case RawNTLMSSP:
		if (!(secFlags & CIFSSEC_MAY_NTLMSSP))
			return false;
		break;
	default:
		/* shouldn't happen */
		return false;
	}

	/* now check if signing mode is acceptible */
	if ((secFlags & CIFSSEC_MAY_SIGN) == 0 &&
	    (server->sec_mode & SECMODE_SIGN_REQUIRED))
			return false;
	else if (((secFlags & CIFSSEC_MUST_SIGN) == CIFSSEC_MUST_SIGN) &&
		 (server->sec_mode &
		  (SECMODE_SIGN_ENABLED|SECMODE_SIGN_REQUIRED)) == 0)
			return false;

	return true;
}