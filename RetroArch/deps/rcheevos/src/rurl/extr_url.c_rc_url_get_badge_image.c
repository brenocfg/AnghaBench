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
 int snprintf (char*,size_t,char*,char const*) ; 

int rc_url_get_badge_image(char* buffer, size_t size, const char* badge_name) {
  int written = snprintf(
    buffer,
    size,
    "http://i.retroachievements.org/Badge/%s",
    badge_name
  );

  return (size_t)written >= size ? -1 : 0;
}