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
typedef  size_t DOHcode ;

/* Variables and functions */
 size_t DOH_DNS_BAD_ID ; 
 size_t DOH_OK ; 
 char const** errors ; 

__attribute__((used)) static const char *doh_strerror(DOHcode code)
{
  if((code >= DOH_OK) && (code <= DOH_DNS_BAD_ID))
    return errors[code];
  return "bad error code";
}