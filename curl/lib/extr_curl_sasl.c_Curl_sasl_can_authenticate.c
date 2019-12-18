#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ user_passwd; } ;
struct connectdata {TYPE_1__ bits; } ;
struct SASL {int authmechs; int prefmech; } ;

/* Variables and functions */
 int FALSE ; 
 int SASL_MECH_EXTERNAL ; 
 int TRUE ; 

bool Curl_sasl_can_authenticate(struct SASL *sasl, struct connectdata *conn)
{
  /* Have credentials been provided? */
  if(conn->bits.user_passwd)
    return TRUE;

  /* EXTERNAL can authenticate without a user name and/or password */
  if(sasl->authmechs & sasl->prefmech & SASL_MECH_EXTERNAL)
    return TRUE;

  return FALSE;
}