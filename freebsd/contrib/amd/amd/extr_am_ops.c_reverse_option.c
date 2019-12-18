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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ NSTREQ (char const*,char*,int) ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char const*,int) ; 

__attribute__((used)) static char *
reverse_option(const char *opt)
{
  static char buf[80];

  /* sanity check */
  if (!opt)
    return NULL;

  /* check special cases */
  /* XXX: if this gets too long, rewrite the code more flexibly */
  if (STREQ(opt, "ro")) return "rw";
  if (STREQ(opt, "rw")) return "ro";
  if (STREQ(opt, "bg")) return "fg";
  if (STREQ(opt, "fg")) return "bg";
  if (STREQ(opt, "soft")) return "hard";
  if (STREQ(opt, "hard")) return "soft";

  /* check if string starts with 'no' and chop it */
  if (NSTREQ(opt, "no", 2)) {
    xstrlcpy(buf, &opt[2], sizeof(buf));
  } else {
    /* finally return a string prepended with 'no' */
    xstrlcpy(buf, "no", sizeof(buf));
    xstrlcat(buf, opt, sizeof(buf));
  }
  return buf;
}