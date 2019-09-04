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
struct SASLproto {int dummy; } ;
struct SASL {void* force_ir; void* mutual_auth; int /*<<< orphan*/  resetprefs; void* authused; int /*<<< orphan*/  prefmech; void* authmechs; int /*<<< orphan*/  state; struct SASLproto const* params; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SASL_AUTH_DEFAULT ; 
 void* SASL_AUTH_NONE ; 
 int /*<<< orphan*/  SASL_STOP ; 
 int /*<<< orphan*/  TRUE ; 

void Curl_sasl_init(struct SASL *sasl, const struct SASLproto *params)
{
  sasl->params = params;           /* Set protocol dependent parameters */
  sasl->state = SASL_STOP;         /* Not yet running */
  sasl->authmechs = SASL_AUTH_NONE; /* No known authentication mechanism yet */
  sasl->prefmech = SASL_AUTH_DEFAULT; /* Prefer all mechanisms */
  sasl->authused = SASL_AUTH_NONE; /* No the authentication mechanism used */
  sasl->resetprefs = TRUE;         /* Reset prefmech upon AUTH parsing. */
  sasl->mutual_auth = FALSE;       /* No mutual authentication (GSSAPI only) */
  sasl->force_ir = FALSE;          /* Respect external option */
}