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
struct SASL {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  saslstate ;

/* Variables and functions */

__attribute__((used)) static void state(struct SASL *sasl, struct connectdata *conn,
                  saslstate newstate)
{
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[]={
    "STOP",
    "PLAIN",
    "LOGIN",
    "LOGIN_PASSWD",
    "EXTERNAL",
    "CRAMMD5",
    "DIGESTMD5",
    "DIGESTMD5_RESP",
    "NTLM",
    "NTLM_TYPE2MSG",
    "GSSAPI",
    "GSSAPI_TOKEN",
    "GSSAPI_NO_DATA",
    "OAUTH2",
    "OAUTH2_RESP",
    "CANCEL",
    "FINAL",
    /* LAST */
  };

  if(sasl->state != newstate)
    infof(conn->data, "SASL %p state change from %s to %s\n",
          (void *)sasl, names[sasl->state], names[newstate]);
#else
  (void) conn;
#endif

  sasl->state = newstate;
}