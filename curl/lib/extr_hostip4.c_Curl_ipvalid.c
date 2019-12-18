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
struct connectdata {scalar_t__ ip_version; } ;

/* Variables and functions */
 scalar_t__ CURL_IPRESOLVE_V6 ; 
 int FALSE ; 
 int TRUE ; 

bool Curl_ipvalid(struct connectdata *conn)
{
  if(conn->ip_version == CURL_IPRESOLVE_V6)
    /* An IPv6 address was requested and we can't get/use one */
    return FALSE;

  return TRUE; /* OK, proceed */
}