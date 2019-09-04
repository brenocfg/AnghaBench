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
struct connectdata {int dummy; } ;

/* Variables and functions */

void Curl_sasl_cleanup(struct connectdata *conn, unsigned int authused)
{
#if defined(USE_KERBEROS5)
  /* Cleanup the gssapi structure */
  if(authused == SASL_MECH_GSSAPI) {
    Curl_auth_gssapi_cleanup(&conn->krb5);
  }
#endif

#if defined(USE_NTLM)
  /* Cleanup the NTLM structure */
  if(authused == SASL_MECH_NTLM) {
    Curl_auth_ntlm_cleanup(&conn->ntlm);
  }
#endif

#if !defined(USE_KERBEROS5) && !defined(USE_NTLM)
  /* Reserved for future use */
  (void)conn;
  (void)authused;
#endif
}