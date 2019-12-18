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
typedef  int ProfileNameSpecifier ;

/* Variables and functions */
#define  PNS_command_line 131 
#define  PNS_default 130 
#define  PNS_environment 129 
#define  PNS_runtime_api 128 

__attribute__((used)) static const char *getPNSStr(ProfileNameSpecifier PNS) {
  switch (PNS) {
  case PNS_default:
    return "default setting";
  case PNS_command_line:
    return "command line";
  case PNS_environment:
    return "environment variable";
  case PNS_runtime_api:
    return "runtime API";
  default:
    return "Unknown";
  }
}