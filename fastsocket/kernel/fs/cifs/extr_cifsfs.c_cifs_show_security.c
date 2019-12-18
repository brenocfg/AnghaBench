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
struct seq_file {int dummy; } ;
struct TCP_Server_Info {int secType; int sec_mode; } ;

/* Variables and functions */
#define  Kerberos 132 
#define  LANMAN 131 
#define  NTLM 130 
#define  NTLMv2 129 
#define  RawNTLMSSP 128 
 int SECMODE_SIGN_ENABLED ; 
 int SECMODE_SIGN_REQUIRED ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static void
cifs_show_security(struct seq_file *s, struct TCP_Server_Info *server)
{
	seq_printf(s, ",sec=");

	switch (server->secType) {
	case LANMAN:
		seq_printf(s, "lanman");
		break;
	case NTLMv2:
		seq_printf(s, "ntlmv2");
		break;
	case NTLM:
		seq_printf(s, "ntlm");
		break;
	case Kerberos:
		seq_printf(s, "krb5");
		break;
	case RawNTLMSSP:
		seq_printf(s, "ntlmssp");
		break;
	default:
		/* shouldn't ever happen */
		seq_printf(s, "unknown");
		break;
	}

	if (server->sec_mode & (SECMODE_SIGN_REQUIRED | SECMODE_SIGN_ENABLED))
		seq_printf(s, "i");
}