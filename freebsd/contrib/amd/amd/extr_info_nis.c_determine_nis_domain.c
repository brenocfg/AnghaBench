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
typedef  int /*<<< orphan*/  default_domain ;
struct TYPE_2__ {int /*<<< orphan*/  nis_domain; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int YPMAXDOMAIN ; 
 scalar_t__ getdomainname (char*,int) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static int
determine_nis_domain(void)
{
  static int nis_not_running = 0;
  char default_domain[YPMAXDOMAIN];

  if (nis_not_running)
    return ENOENT;

  if (getdomainname(default_domain, sizeof(default_domain)) < 0) {
    nis_not_running = 1;
    plog(XLOG_ERROR, "getdomainname: %m");
    return EIO;
  }
  if (!*default_domain) {
    nis_not_running = 1;
    plog(XLOG_WARNING, "NIS domain name is not set.  NIS ignored.");
    return ENOENT;
  }
  gopt.nis_domain = xstrdup(default_domain);

  return 0;
}