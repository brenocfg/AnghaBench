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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ curl_strnequal (char const*,char*,int) ; 

__attribute__((used)) static bool is_pkcs11_uri(const char *string)
{
  if(curl_strnequal(string, "pkcs11:", 7)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}